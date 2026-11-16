// keysend —— 向指定应用发送虚拟键盘事件（用于验证菜单能否纯键盘导航）
//
// 编译：clang -fobjc-arc -O2 -o keysend keysend.m -framework Foundation -framework AppKit
// 用法：
//   ./keysend list                     列出可激活的目标
//   ./keysend activate <bundleId|名字>  把目标置前台
//   ./keysend tap <keycode> [次数]       发送按键（默认 1 次，间隔 120 ms）
//   ./keysend seq "125,125,36"         发送序列（逗号分隔 keycode）
//
// 常用 keycode：上 126 / 下 125 / 左 123 / 右 124 / Return 36 / Escape 53 / Tab 48

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <Carbon/Carbon.h>

static void postKey(CGKeyCode code, BOOL down)
{
    CGEventRef e = CGEventCreateKeyboardEvent(NULL, code, down);
    CGEventPost(kCGHIDEventTap, e);
    CFRelease(e);
}

static void tapKey(CGKeyCode code)
{
    postKey(code, YES);
    usleep(40 * 1000);
    postKey(code, NO);
    usleep(80 * 1000);
}

static NSRunningApplication *findApp(NSString *arg)
{
    for (NSRunningApplication *a in [[NSWorkspace sharedWorkspace] runningApplications]) {
        if ([a.bundleIdentifier isEqualToString:arg] ||
            [a.localizedName isEqualToString:arg])
            return a;
    }
    return nil;
}

int main(int argc, char **argv)
{
    @autoreleasepool {
        if (argc < 2) {
            fprintf(stderr, "用法: keysend list | activate <名字> | tap <keycode> [n] | seq \"125,125,36\"\n");
            return 2;
        }
        NSString *cmd = @(argv[1]);

        if ([cmd isEqualToString:@"list"]) {
            for (NSRunningApplication *a in [[NSWorkspace sharedWorkspace] runningApplications]) {
                if (a.activationPolicy != NSApplicationActivationPolicyProhibited && a.localizedName)
                    printf("%-40s %s\n", a.localizedName.UTF8String,
                           a.bundleIdentifier.UTF8String ?: "-");
            }
            return 0;
        }
        if ([cmd isEqualToString:@"activate"]) {
            if (argc < 3) return 2;
            NSRunningApplication *a = findApp(@(argv[2]));
            if (!a) { printf("找不到应用: %s\n", argv[2]); return 1; }
            BOOL ok = [a activateWithOptions:NSApplicationActivateIgnoringOtherApps];
            usleep(400 * 1000);
            printf("activate %s -> %s (frontmost=%s)\n", a.localizedName.UTF8String,
                   ok ? "ok" : "fail",
                   [NSWorkspace sharedWorkspace].frontmostApplication.localizedName.UTF8String);
            return 0;
        }
        if ([cmd isEqualToString:@"tap"]) {
            if (argc < 3) return 2;
            int n = argc > 3 ? atoi(argv[3]) : 1;
            CGKeyCode code = (CGKeyCode)atoi(argv[2]);
            for (int i = 0; i < n; i++)
                tapKey(code);
            printf("tap keycode=%d ×%d\n", (int)code, n);
            return 0;
        }
        if ([cmd isEqualToString:@"seq"]) {
            if (argc < 3) return 2;
            NSString *s = @(argv[2]);
            for (NSString *p in [s componentsSeparatedByString:@","]) {
                int v = p.intValue;
                if (v > 0) {
                    tapKey((CGKeyCode)v);
                    printf("  tap %d\n", v);
                }
            }
            return 0;
        }
        fprintf(stderr, "未知子命令: %s\n", argv[1]);
        return 2;
    }
}
