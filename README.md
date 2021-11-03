# Windows 11 Drag & Drop to the Taskbar (Fix)

This program fixes the missing "Drag & Drop to the Taskbar" support in Windows 11. In the best case, such a simple and basic functionality will return to Windows 11 in October 2022 (or never). For now, we have to use workarounds in the OS that was supposed to "empower our productivity".

Windows11DragAndDropToTaskbarFix works with the new Windows 11 taskbar and does not require nasty changes like `UndockingDisabled` or restoration of the `classic taskbar`. It doesn't change any system registry keys (except autostart for itself when manually configured) and does not inject any DLLs to other processes, so it's a very portable solution. This program will not interrupt further windows updates as it doesn't change any system files. It's an independent C++ process that does all the job.

### [Download Binary (Windows11DragAndDropToTaskbarFix.exe)](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/)

### [Read the Changelog](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CHANGELOG.md)

### [View the source code (Windows11DragAndDropToTaskbarFix.cpp)](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/Windows11DragAndDropToTaskbarFix/Windows11DragAndDropToTaskbarFix.cpp)


## **How Does It Work?**
<img align="right" src="https://user-images.githubusercontent.com/24290461/140068775-473a45f7-1f6a-4b10-8664-e5f8d49440ab.png">

The program detects if you're currently pressing the Left or the Right Mouse Button and determines which icon on the taskbar you hover the mouse pointer on. If the cursor stays in the same area for definied number of milliseconds - it simulates the `Win+T` hotkey and arrow keys in order to restore the intended window, using a quite complicated method. It also supports dropping files to the "Show desktop" button (bottom-right of the screen). The program supports multiple screens, auto startup, and has many configuration options (please read below). Windows11DragAndDropToTaskbarFix has no auto-update function and never connects to the Internet, so you don't need to worry about your privacy.
You can click on the Mona Lisa Megan Fox tray icon in order to menu that allows you to `Check for updates`, `Read the changelog`, `Configure`, `Open program folder`, `Restart` and `Quit`.


## **Custom Configuration: Autostart, Timings, Keys Remapping and more**
It's possible to configure the program by creating a configuration file at the same location as `Windows11DragAndDropToTaskbarFix.exe`. The configuration file should be named: `Windows11DragAndDropToTaskbarFixConfig.txt`. You can automate this process by clicking on the Mona Lisa Megan Fox `Tray icon` and then `Configure...` from the menu. It will create the correct file and open the GitHub page for reference.

Please read a separate article: [CONFIGURATION](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CONFIGURATION.md) for details.


## **Limitations**
- The program does not support pinning apps to the taskbar using the drag and drop gesture, and this feature is currently not planned. However, you still can pin apps to the taskbar by clicking on their icons with the right mouse button, and then "Pin to taskbar" from the list.

- I'm not aware of any serious limitations in the current version. Please check [#issues](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues)


## **How to Start or Quit the Program?**

To use the fix, please simply download the binary file above (or compile it yourself) and **start it as any other program**. It works as an independent C++ process.

To quit this program, please click on the Mona Lisa Megan Fox Tray icon, and select "Quit..." from the menu. You can also **kill** `Windows11DragAndDropToTaskbarFix.exe` or `Windows 11 Drag & Drop to the Taskbar (Fix)` **by the Task Manager**.


## Special Thanks To:
- **Martin Morano** for giving permissions to use his awesome "Mona Lisa Megan Fox" artwork (used as the program icon).


### "VCRUNTIME140_1.dll" was not found error
If you get an error saying that "VCRUNTIME140_1.dll" is missing, please install [Microsoft Visual C++ 2015 - 2019 Redistributable x64](https://aka.ms/vs/16/release/vc_redist.x64.exe). Normally, these runtime libraries are installed by default on Windows 11. If you get this error then you most likely manually removed them before, using "Add or remove programs".


### **New Ideas Are Welcome**

If you have any idea how to improve this program, or if you found a different method of determining the window under the cursor - please share it with us!


### **Code Quality**

It's not beautiful, but it works. I also believe that it has been well-optimized by the dynamic thread sleep times and avoiding unnecessary steps (depending on the mouse button click time). Please feel free to issue pull requests to improve it. The software will for sure be updated by me, I just wanted to share it with people as soon as possible. Microsoft seems to do the same thing with their Operating System :)


### **Donation?**

If you love this software so much that you would like to buy me a cola, pizza, or anything else - you can make a donation using the button available on my other project's website: [Click here](https://ee2.eu/overview/#donate). Please don't forget to mention in the donation message that it's for this fix :)
