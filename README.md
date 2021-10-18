# Windows 11 Drag & Drop to the Taskbar (Fix)

This program fixes the missing "Drag & Drop to the Taskbar" support in Windows 11. In the best case, such a simple and basic functionality will return to Windows 11 in October 2022 (or never). For now, we have to use workarounds in the OS that was supposed to "empower our productivity".

Windows11DragAndDropToTaskbarFix works with the new Windows 11 taskbar and does not require nasty changes like `UndockingDisabled` or restoration of the `classic taskbar`.

[Download Binary (Windows11DragAndDropToTaskbarFix.exe)](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/)

[Read the Changelog](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CHANGELOG.md)

[View the source code (Windows11DragAndDropToTaskbarFix.cpp)](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/Windows11DragAndDropToTaskbarFix/Windows11DragAndDropToTaskbarFix.cpp)

### **How Does It Work?**

The program detects if you're currently pressing the left mouse button and determines which icon on the taskbar you hover the mouse pointer on. If the cursor stays in the same area for X milliseconds - it simulates the `Win+Ctrl+Number` hotkey (open the desktop and switch to the last active window of the app pinned to the taskbar in the position indicated by the number), in order to restore the intended window. It also supports dropping files to the "Show desktop" button (bottom-right of the screen). The program supports auto startup and has many configuration options (please read below).

### **Limitations**

I'm not aware of any limitations in the current version. Please check [#issues](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues)

### **How to Start or Quit the Program?**

To use the fix, please simply download the binary file above (or compile it yourself) and **start it as any other program**. It works as an independent C++ process. It does not change any registry keys (with the exception of the autostart key for itself) and does not inject any DLLs to other processes.

To quit this program, please **simply kill** `Windows11DragAndDropToTaskbarFix.exe` or `Windows 11 Drag & Drop to the Taskbar (Fix)` **by the Task Manager**.

### **Configuration**
Since version 1.1 it's possible to configure the program by creating a configuration file at the same location as `Windows11DragAndDropToTaskbarFix.exe`. The configuration file should be named: `Windows11DragAndDropToTaskbarFixConfig.txt` and may contain the following variables:

```
//Should the program run automatically on system startup? 1 = true, 0 = false.
AutomaticallyRunThisProgramOnStartup=1

//Should the program show the console window when it starts? 1 = true, 0 = false.
ShowConsoleWindowOnStartup=1

//Should the program print debug information? 1 = true, 0 = false.
PrintDebugInfo=0

//Should the program use ver. 1.2.0 improvements that remove all previous limitations? 1 = true, 0 = false.
UseTheNewBestMethodEver=1

//Sleep time (in milliseconds) between simulating different keys in the new "BestMethodEver"
HowLongSleepBetweenDifferentKeysPressMilliseconds=10

//Sleep time (in milliseconds) between simulating the same keys in the new "BestMethodEver" 
HowLongSleepBetweenTheSameKeysPressMilliseconds=0

//For how long (in milliseconds) should the left mouse button be clicked before
//the program starts checking if the mouse is hovering over the task bar.
HowLongLeftMouseButtonPressedBeforeContinueMilliseconds=750

//For how long (in milliseconds) should the mouse be hovered over the same icon
//on taskbar in order to restore its window.
HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds=200

//You can skip options below. It's only to change main thread sleeping times or default icon sizes.
DefaultSleepPeriodInTheLoopMilliseconds=100
SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds=25
SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds=10
DefaultTaskbarIconWidth=44
DefaultTaskbarIconHeight=48
DefaultShowDesktopButtonWidth=20
```

When you modify the `Windows11DragAndDropToTaskbarFixConfig.txt`, the program will ask you to automatically restart itself. So you don't need to go to the Task Manager each time you want to test something.

### **New Ideas Are Welcome**

If you have any idea how to improve this program, or if you found a different method of determining the window under the cursor - please share it with us!

### **Code Quality**

It's not beautiful, but it works. I also believe that the optimization is good by the dynamic thread sleep times. Please feel free to issue pull requests to improve it. The software will for sure be updated by me, I just wanted to share it with people as soon as possible. Microsoft seems to do the same thing with their Operating System :)
