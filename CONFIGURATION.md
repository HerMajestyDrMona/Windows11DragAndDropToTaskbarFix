## **Custom Configuration**

Since version 1.1 it's possible to configure the program by creating a configuration file at the same location as `Windows11DragAndDropToTaskbarFix.exe`. The configuration file should be named: `Windows11DragAndDropToTaskbarFixConfig.txt`. You can automate this process by clicking on the Mona Lisa Megan Fox `Tray icon` and then `Configure...` from the menu. It will create the correct file and open this GitHub page for reference.

When you modify `Windows11DragAndDropToTaskbarFixConfig.txt`, the program will ask you to automatically restart itself. So you don't need to go to the Task Manager each time you want to test something.

You can include the following variables to your `Windows11DragAndDropToTaskbarFixConfig.txt` file:

```
//Should the program run automatically on system startup? 1 = true, 0 = false.
AutomaticallyRunThisProgramOnStartup=0

//Should the program show the console window when it starts? 1 = true, 0 = false.
ShowConsoleWindowOnStartup=0

//Should the program print debug information? 1 = true, 0 = false.
PrintDebugInfo=0

//Should the program use a fix after detecting a wake up from the Sleep Mode? It fixes issues where the
//program did not work correctly before ver. 1.5.1. 1 = true, 0 = false.
UseFixForBugAfterSleepMode=1

//Should the program show the Tray Icon in the system tray? Available since ver 1.8. 1 = true, 0 = false.
ShowTrayIcon=1

//Should the program use ver. 1.2.0 improvements that remove all previous limitations? 1 = true, 0 = false.
UseTheNewBestMethodEver=1

//Available since ver. 1.3. Should the program automatically open the first active window under the cursor,
//except pinned apps with no active window? 1 = true, 0 = false, 2 = only if no more than 1 window under the icon.
AutoOpenFirstWindowInBestMethodEver=2

//Sleep time (in milliseconds) between simulating different keys in the new "BestMethodEver"
HowLongSleepBetweenDifferentKeysPressMilliseconds=10

//Sleep time (in milliseconds) between simulating the same keys in the new "BestMethodEver" 
HowLongSleepBetweenTheSameKeysPressMilliseconds=0

//Sleep time (in milliseconds) after opening the first window under the icon in the new "BestMethodEver"
HowLongSleepAfterAutoOpenFirstWindowMilliseconds=100

//Delay (in milliseconds) before opening the first window under the icon in the new "BestMethodEver"
HowLongKeepMouseOverAppIconBeforeAutoOpeningMilliseconds=550

//Timeout (in milliseconds) after which the program interrupts the loop where it's detecting for the
//preview window changes. It's to avoid opening pinned apps with no active window. It can be a greater
//value, becauseit's a non-blocking loop which usually breaks much quicker. Only for "BestMethodEver".
PreviewWindowChangeDetectionMaxMilliseconds=1000

//For how long (in milliseconds) should the left mouse button be clicked before
//the program starts checking if the mouse is hovering over the task bar.
HowLongLeftMouseButtonPressedBeforeContinueMilliseconds=750

//For how long (in milliseconds) should the mouse be hovered over the same icon
//on taskbar in order to restore its window.
HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds=200

//Since ver. 1.8 it's possible to remap keys used by the program. Please use
//https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
//to find the right value (0x...). This allows simulating different keys instead of default ones.
REMAP_VK_LWIN=0x5B
REMAP_VK_MENU=0x12
REMAP_VK_TAB=0x09
REMAP_VK_LCONTROL=0xA2
REMAP_VK_LSHIFT=0xA0
REMAP_VK_LEFT=0x25
REMAP_VK_RIGHT=0x27
REMAP_VK_UP=0x26
REMAP_VK_DOWN=0x28
REMAP_VK_RETURN=0x0D
REMAP_VK_D=0x44
REMAP_VK_T=0x54

//You can skip options below. It's only to change main thread sleeping times or default icon sizes.
DefaultSleepPeriodInTheLoopMilliseconds=100
SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds=25
SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds=10
DefaultTaskbarIconWidth=44
DefaultTaskbarIconHeight=48
DefaultShowDesktopButtonWidth=20
ConfigFileChangeTimeMonitorAllowed=1
```


