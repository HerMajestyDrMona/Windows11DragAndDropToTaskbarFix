# Windows 11 Drag & Drop to the Taskbar (Partial Fix)

This program partially fixes the missing "Drag & Drop to the Taskbar" support in Windows 11. In the best case, such a simple and basic functionality will return to Windows 11 in October 2022 (or never). For now, we have to use workarounds in the OS that "empowers our productivity".

Windows11DragAndDropToTaskbarPartialFix works with the new Windows 11 taskbar and does not require nasty changes like `UndockingDisabled` or restoration of the classic taskbar.

[Download Binary](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix/releases/)

**How Does It Work?**

The program detects if you're currently pressing the left mouse button and determines which icon on the taskbar you hover the mouse pointer on. If the cursor stays in the same area for X milliseconds - it simulates the `Win+Ctrl+Number` hotkey (open the desktop and switch to the last active window of the app pinned to the taskbar in the position indicated by the number), in order to restore the right window. It also supports dropping files to the "Show desktop" button (bottom-right of the screen).

**Limitations**

* Unfortunately, Windows only supports 10 hotkeys of this type: `Win+Ctrl+1` to `Win+Ctrl+0`. It means that the fix will only work for the first 10 apps on the taskbar. I know it's a very low limit, but might be useful if you keep the Internet Browser / Messengers in the first position on the taskbar.
* If the pinned app icon currently has no visible window, the fix will start it. It's a different behaviour than the one we remember, but I personally found it useful, for example because it's restoring the Skype window when it's active in the System Tray only.
* It doesn't support multiple windows of the same process :(

**New Ideas Are Welcome**

If you have any idea how to improve this program, or if you found a different method of determining the window under the cursor - please share it with us!

**Code Quality**

It's not beautiful, but it works. I also believe that the optimization is good by the dynamic thread sleep times. Please feel free to issue pull requests to improve it. The software will for sure be updated by me, I just wanted to share it with people as soon as possible. Microsoft seems to do the same thing with their Operating System :)
