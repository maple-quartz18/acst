// vpad —— macOS 虚拟手柄探针（IOHIDUserDevice）
//
// 目标：按 iOS 侧 TouchController 先例的三层判据验证 Mac 端虚拟手柄可用性
//   ① 出现在 GCController.controllers 且收到 GCControllerDidConnectNotification
//   ② extendedGamepad profile 完整可读
//   ③ 程序化改变输入态后 buttonA.isPressed 真值翻转
//
// 编译：clang -fobjc-arc -O2 -o vpad vpad.m \
//         -framework Foundation -framework IOKit -framework GameController
// 运行：./vpad [发现等待秒数=6]
//
// 可选环境变量：
//   VPAD_XBOX=1    使用 Xbox 风格 VID/PID（0x045E/0x02EA）与 Transport=USB
//   VPAD_TRANSPORT=USB|Bluetooth

#import <Foundation/Foundation.h>
#import <IOKit/hidsystem/IOHIDUserDevice.h>
#import <GameController/GameController.h>

static uint8_t kDesc[] = {
    0x05, 0x01,        // Usage Page (Generic Desktop)
    0x09, 0x05,        // Usage (Gamepad)
    0xA1, 0x01,        // Collection (Application)
    // 16 个按钮，每按钮 1 bit
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x35, 0x00, 0x45, 0x01,
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x10,        //   Report Count (16)
    0x05, 0x09,        //   Usage Page (Button)
    0x19, 0x01, 0x29, 0x10,   //   Usage 1..16
    0x81, 0x02,        //   Input (Data,Var,Abs)
    // 4 个轴：X Y Z Rz，8 位有符号
    0x05, 0x01,
    0x09, 0x30, 0x09, 0x31, 0x09, 0x32, 0x09, 0x35,
    0x15, 0x81, 0x25, 0x7F,   //   Logical -127..127
    0x75, 0x08, 0x95, 0x04,
    0x81, 0x02,
    // 十字键（hat）
    0x09, 0x39,
    0x15, 0x00, 0x25, 0x07,
    0x35, 0x00, 0x46, 0x3B, 0x01,
    0x65, 0x14,        //   Unit (degrees)
    0x75, 0x04, 0x95, 0x01,
    0x81, 0x42,        //   Input (Data,Var,Abs,Null)
    0x65, 0x00,
    0x75, 0x04, 0x95, 0x01,
    0x81, 0x03,        //   余下 4 bit 填充
    0xC0
};

// 报告布局（7 字节）：[0..1] 按钮位图，[2..5] X/Y/Z/Rz，[6] hat
#define kReportLen 7

static IOHIDUserDeviceRef gDev = NULL;

static BOOL sendReport(uint8_t buttonsLow, uint8_t buttonsHigh,
                       int8_t x, int8_t y, int8_t z, int8_t rz, uint8_t hat)
{
    uint8_t r[kReportLen] = { buttonsLow, buttonsHigh, (uint8_t)x, (uint8_t)y,
                              (uint8_t)z, (uint8_t)rz, (uint8_t)(hat & 0x0F) };
    IOReturn ret = IOHIDUserDeviceHandleReportWithTimeStamp(gDev, 0, r, kReportLen);
    if (ret != kIOReturnSuccess)
        printf("handleReport 失败: 0x%x\n", ret);
    return ret == kIOReturnSuccess;
}

static void spin(CFTimeInterval sec)
{
    [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode
                             beforeDate:[NSDate dateWithTimeIntervalSinceNow:sec]];
}

static void dumpControllers(const char *tag)
{
    NSArray<GCController *> *list = [GCController controllers];
    printf("[%s] controllers=%lu\n", tag, (unsigned long)list.count);
    for (GCController *c in list) {
        GCExtendedGamepad *pad = c.extendedGamepad;
        printf("  vendor=%s category=%s ext=%s A=%s\n",
               c.vendorName.UTF8String ?: "-",
               c.productCategory.UTF8String ?: "-",
               pad ? "yes" : "no",
               (pad && pad.buttonA) ? "yes" : "no");
    }
}

int main(int argc, char **argv)
{
    @autoreleasepool {
        int waitSec = argc > 1 ? atoi(argv[1]) : 6;

        BOOL xbox = getenv("VPAD_XBOX") != NULL;
        NSString *transport = getenv("VPAD_TRANSPORT") ? @(getenv("VPAD_TRANSPORT")) : @"USB";

        NSMutableDictionary *props = [@{
            @kIOHIDReportDescriptorKey: [NSData dataWithBytes:kDesc length:sizeof kDesc],
            @kIOHIDProductKey: @"AC Virtual Pad",
            @kIOHIDManufacturerKey: @"AC",
            @kIOHIDPrimaryUsagePageKey: @(1),
            @kIOHIDPrimaryUsageKey: @(5),
        } mutableCopy];
        // Xbox 风格标识（部分系统对未知 VID/PID 的 HID 设备不做 GameController 归类）
        props[@kIOHIDVendorIDKey] = xbox ? @(0x045E) : @(0x0F0D);
        props[@kIOHIDProductIDKey] = xbox ? @(0x02EA) : @(0x0092);
        if (transport.length)
            props[@kIOHIDTransportKey] = transport;

        gDev = IOHIDUserDeviceCreateWithProperties(kCFAllocatorDefault,
                                                    (__bridge CFDictionaryRef)props, 0);
        if (!gDev) {
            printf("IOHIDUserDeviceCreateWithProperties 失败（属性集被系统拒绝）\n");
            return 1;
        }
        IOHIDUserDeviceSetDispatchQueue(gDev, dispatch_get_main_queue());
        IOHIDUserDeviceActivate(gDev);
        printf("虚拟手柄已创建 (xbox=%d transport=%s)\n", xbox ? 1 : 0, transport.UTF8String);

        // 中位报告：无按键、轴居中、hat 居中
        sendReport(0, 0, 0, 0, 0, 0, 8);

        __block int connectNotify = 0;
        NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
        id obs = [nc addObserverForName:GCControllerDidConnectNotification
                                  object:nil queue:nil
                              usingBlock:^(NSNotification *n) {
            connectNotify++;
            printf("通知: GCControllerDidConnect -> %s\n",
                   [[n.object description] UTF8String] ?: "-");
        }];

        printf("--- 等待 %d 秒让 GameController 发现设备 ---\n", waitSec);
        for (int i = 0; i < waitSec * 2; i++) {
            spin(0.5);
            if ([GCController controllers].count > 0)
                break;
        }
        dumpControllers("① 发现");

        GCController *target = [GCController controllers].firstObject;
        GCExtendedGamepad *pad = target.extendedGamepad;
        printf("② profile: %s", pad ? "存在\n" : "缺失\n");
        if (!pad) {
            printf("结论：虚拟手柄未被 GameController 归类（可能被过滤，可试 VPAD_XBOX=1）\n");
            [nc removeObserver:obs];
            return 2;
        }

        BOOL before = pad.buttonA.isPressed;
        printf("③ 按下前 isPressed=%d\n", before ? 1 : 0);

        sendReport(0x01, 0, 0, 0, 0, 0, 8);   // bit0 = button1 = A
        for (int i = 0; i < 6; i++)
            spin(0.05);
        BOOL pressed = pad.buttonA.isPressed;
        printf("   按下后 isPressed=%d\n", pressed ? 1 : 0);

        sendReport(0, 0, 0, 0, 0, 0, 8);
        for (int i = 0; i < 6; i++)
            spin(0.05);
        BOOL released = pad.buttonA.isPressed;
        printf("   抬起后 isPressed=%d\n", released ? 1 : 0);

        printf("结论：① controllers=%lu 通知=%d | ② ext=%d | ③ 翻转=%s\n",
               (unsigned long)[GCController controllers].count, connectNotify,
               pad ? 1 : 0,
               (!before && pressed && !released) ? "成立" : "不成立");

        [nc removeObserver:obs];
        spin(0.2);
    }
    return 0;
}
