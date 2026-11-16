// vpadroot —— 以 root 运行的虚拟手柄 helper（IOHIDUserDevice）
//
// 为什么需要 root：macOS 对 IOHIDUserDevice 的创建有权限校验，普通用户进程会失败
// （见 tools/vpad.m 的实测）。本工具必须以 root 运行，且不依赖关闭 SIP。
//
// 编译：
//   clang -fobjc-arc -O2 -isysroot <MacOSX27.2.sdk> -o vpadroot vpadroot.m \
//     -framework Foundation -framework IOKit -framework GameController
//
// 用法：
//   sudo ./vpadroot --test              自检：创建设备、三层判据、打印结果后退出
//   sudo ./vpadroot --serve [socket]    常驻，监听命令（默认 /tmp/vpad.sock）
//
// 命令协议（一行一条，回复一行 "ok" / "err ..."）：
//   press <button>      按下按钮（a/b/x/y/lb/rb/up/down/left/right）
//   release <button>    抬起按钮
//   tap   <button>      按下 40 ms 后抬起
//   seq   a,b,down,a    依次 tap，间隔 200 ms
//   stick <x> <y>       左摇杆（-127..127）
//   hat   <0-8>         十字键（8=居中）
//   state               回显当前按钮位图与摇杆
//   quit                退出

#import <Foundation/Foundation.h>
#import <IOKit/hidsystem/IOHIDUserDevice.h>
#import <GameController/GameController.h>
#import <sys/stat.h>
#import <sys/socket.h>
#import <sys/un.h>
#import <unistd.h>

static uint8_t kDesc[] = {
    0x05, 0x01, 0x09, 0x05, 0xA1, 0x01,
    0x15, 0x00, 0x25, 0x01, 0x35, 0x00, 0x45, 0x01,
    0x75, 0x01, 0x95, 0x10, 0x05, 0x09, 0x19, 0x01, 0x29, 0x10, 0x81, 0x02,
    0x05, 0x01, 0x09, 0x30, 0x09, 0x31, 0x09, 0x32, 0x09, 0x35,
    0x15, 0x81, 0x25, 0x7F, 0x75, 0x08, 0x95, 0x04, 0x81, 0x02,
    0x09, 0x39, 0x15, 0x00, 0x25, 0x07, 0x35, 0x00, 0x46, 0x3B, 0x01,
    0x65, 0x14, 0x75, 0x04, 0x95, 0x01, 0x81, 0x42, 0x65, 0x00,
    0x75, 0x04, 0x95, 0x01, 0x81, 0x03, 0xC0
};

#define kReportLen 7

static IOHIDUserDeviceRef gDev = NULL;
static uint16_t gButtons = 0;      // bit0=A bit1=B bit2=X bit3=Y bit4=LB bit5=RB
static int8_t gX = 0, gY = 0;
static uint8_t gHat = 8;

static BOOL flush(void)
{
    uint8_t r[kReportLen] = { (uint8_t)(gButtons & 0xFF), (uint8_t)(gButtons >> 8),
                              (uint8_t)gX, (uint8_t)gY, 0, 0, (uint8_t)(gHat & 0x0F) };
    IOReturn ret = IOHIDUserDeviceHandleReportWithTimeStamp(gDev, 0, r, kReportLen);
    if (ret != kIOReturnSuccess)
        fprintf(stderr, "handleReport: 0x%x\n", ret);
    return ret == kIOReturnSuccess;
}

static int buttonBit(NSString *n)
{
    NSDictionary *m = @{ @"a": @0, @"b": @1, @"x": @2, @"y": @3, @"lb": @4, @"rb": @5,
                         @"up": @6, @"down": @7, @"left": @8, @"right": @9 };
    NSNumber *v = m[n.lowercaseString];
    return v ? v.intValue : -1;
}

static void spin(CFTimeInterval s)
{
    [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode
                             beforeDate:[NSDate dateWithTimeIntervalSinceNow:s]];
}

static void dumpControllers(const char *tag)
{
    NSArray<GCController *> *list = [GCController controllers];
    printf("[%s] controllers=%lu\n", tag, (unsigned long)list.count);
    for (GCController *c in list) {
        GCExtendedGamepad *p = c.extendedGamepad;
        printf("  vendor=%s category=%s ext=%s A=%s\n",
               c.vendorName.UTF8String ?: "-", c.productCategory.UTF8String ?: "-",
               p ? "yes" : "no", (p && p.buttonA) ? "yes" : "no");
    }
}

static BOOL createDevice(void)
{
    BOOL xbox = getenv("VPAD_XBOX") != NULL;
    NSString *transport = getenv("VPAD_TRANSPORT") ? @(getenv("VPAD_TRANSPORT")) : @"USB";
    NSMutableDictionary *props = [@{
        @kIOHIDReportDescriptorKey: [NSData dataWithBytes:kDesc length:sizeof kDesc],
        @kIOHIDProductKey: @"AC Virtual Pad",
        @kIOHIDManufacturerKey: @"AC",
        @kIOHIDPrimaryUsagePageKey: @(1),
        @kIOHIDPrimaryUsageKey: @(5),
        @kIOHIDVendorIDKey: xbox ? @(0x045E) : @(0x0F0D),
        @kIOHIDProductIDKey: xbox ? @(0x02EA) : @(0x0092),
    } mutableCopy];
    if (transport.length) props[@kIOHIDTransportKey] = transport;

    gDev = IOHIDUserDeviceCreateWithProperties(kCFAllocatorDefault,
                                               (__bridge CFDictionaryRef)props, 0);
    if (!gDev) {
        printf("创建失败（root=%d xbox=%d transport=%s）\n", geteuid() == 0, xbox,
               transport.UTF8String ?: "-");
        return NO;
    }
    IOHIDUserDeviceSetDispatchQueue(gDev, dispatch_get_main_queue());
    IOHIDUserDeviceActivate(gDev);
    printf("虚拟手柄已创建（root=%d xbox=%d transport=%s）\n", geteuid() == 0, xbox,
           transport.UTF8String ?: "-");
    flush();
    return YES;
}

static int runTest(void)
{
    if (!createDevice()) return 1;
    for (int i = 0; i < 12; i++) {
        spin(0.5);
        if ([GCController controllers].count > 0) break;
    }
    dumpControllers("① 发现");

    GCController *c = [GCController controllers].firstObject;
    GCExtendedGamepad *p = c.extendedGamepad;
    printf("② profile: %s\n", p ? "存在" : "缺失");
    if (!p) return 2;

    BOOL before = p.buttonA.isPressed;
    gButtons |= 1; flush();
    spin(0.3);
    BOOL pressed = p.buttonA.isPressed;
    gButtons &= ~1; flush();
    spin(0.3);
    BOOL after = p.buttonA.isPressed;
    printf("③ isPressed: before=%d pressed=%d after=%d\n", before, pressed, after);
    printf("结论: %s\n", (!before && pressed && !after) ? "通过（虚拟手柄可用）" : "未通过");
    return (!before && pressed && !after) ? 0 : 3;
}

static int runServe(const char *sockPath)
{
    if (!createDevice()) return 1;

    unlink(sockPath);
    int srv = socket(AF_UNIX, SOCK_STREAM, 0);
    if (srv < 0) { perror("socket"); return 1; }
    struct sockaddr_un a = {0};
    a.sun_family = AF_UNIX;
    snprintf(a.sun_path, sizeof a.sun_path, "%s", sockPath);
    if (bind(srv, (struct sockaddr *)&a, sizeof a) < 0) { perror("bind"); return 1; }
    listen(srv, 4);
    chmod(sockPath, 0666);
    printf("监听 %s（按 Ctrl-C 退出）\n", sockPath);
    fflush(stdout);

    for (;;) {
        int cli = accept(srv, NULL, NULL);
        if (cli < 0) continue;
        FILE *f = fdopen(cli, "r+");
        char line[512];
        while (fgets(line, sizeof line, f)) {
            size_t n = strlen(line);
            while (n && (line[n - 1] == '\n' || line[n - 1] == '\r')) line[--n] = 0;
            char cmd[64] = {0}, arg1[128] = {0}, arg2[128] = {0};
            sscanf(line, "%63s %127s %127s", cmd, arg1, arg2);
            NSString *c = @(cmd);

            if ([c isEqualToString:@"press"] || [c isEqualToString:@"release"]) {
                int bit = buttonBit(@(arg1));
                if (bit < 0) { fprintf(f, "err button\n"); fflush(f); continue; }
                if ([c isEqualToString:@"press"]) gButtons |= (1 << bit);
                else gButtons &= ~(1 << bit);
                flush();
            } else if ([c isEqualToString:@"tap"]) {
                int bit = buttonBit(@(arg1));
                if (bit < 0) { fprintf(f, "err button\n"); fflush(f); continue; }
                gButtons |= (1 << bit); flush(); spin(0.04);
                gButtons &= ~(1 << bit); flush();
            } else if ([c isEqualToString:@"seq"]) {
                for (NSString *part in [@(arg1) componentsSeparatedByString:@","]) {
                    int bit = buttonBit(part);
                    if (bit < 0) continue;
                    gButtons |= (1 << bit); flush(); spin(0.04);
                    gButtons &= ~(1 << bit); flush(); spin(0.2);
                }
            } else if ([c isEqualToString:@"stick"]) {
                gX = (int8_t)atoi(arg1); gY = (int8_t)atoi(arg2); flush();
            } else if ([c isEqualToString:@"hat"]) {
                gHat = (uint8_t)atoi(arg1); flush();
            } else if ([c isEqualToString:@"state"]) {
                fprintf(f, "buttons=0x%02x hat=%u stick=%d,%d\n", gButtons, gHat, gX, gY);
                fflush(f);
                continue;
            } else if ([c isEqualToString:@"quit"]) {
                fprintf(f, "ok\n"); fflush(f);
                fclose(f);
                goto done;
            } else {
                fprintf(f, "err cmd\n"); fflush(f);
                continue;
            }
            fprintf(f, "ok\n");
            fflush(f);
        }
        fclose(f);
    }
done:
    close(srv);
    unlink(sockPath);
    return 0;
}

int main(int argc, char **argv)
{
    @autoreleasepool {
        if (geteuid() != 0)
            printf("警告：当前非 root（euid=%d），设备创建很可能失败\n", geteuid());

        BOOL test = NO, serve = NO;
        const char *sockPath = "/tmp/vpad.sock";
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "--test")) test = YES;
            else if (!strcmp(argv[i], "--serve")) {
                serve = YES;
                if (i + 1 < argc && argv[i + 1][0] != '-') sockPath = argv[++i];
            }
        }
        if (test) return runTest();
        if (serve) return runServe(sockPath);
        fprintf(stderr, "用法: sudo ./vpadroot --test | --serve [socket]\n");
        return 2;
    }
}
