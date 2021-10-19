## **Custom Configuration**

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

//Available since ver. 1.3. Should the program automatically open the first active window under the cursor,
//except pinned apps with no active window? 1 = true, 0 = false.
AutoOpenFirstWindowInBestMethodEver=1

//Sleep time (in milliseconds) between simulating different keys in the new "BestMethodEver"
HowLongSleepBetweenDifferentKeysPressMilliseconds=10

//Sleep time (in milliseconds) between simulating the same keys in the new "BestMethodEver" 
HowLongSleepBetweenTheSameKeysPressMilliseconds=0

//Sleep time (in milliseconds) after opening the first window under the icon in the new "BestMethodEver"
HowLongSleepAfterAutoOpenFirstWindowMilliseconds=100

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

//You can skip options below. It's only to change main thread sleeping times or default icon sizes.
DefaultSleepPeriodInTheLoopMilliseconds=100
SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds=25
SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds=10
DefaultTaskbarIconWidth=44
DefaultTaskbarIconHeight=48
DefaultShowDesktopButtonWidth=20
```

When you modify the `Windows11DragAndDropToTaskbarFixConfig.txt`, the program will ask you to automatically restart itself. So you don't need to go to the Task Manager each time you want to test something.

Please note that I'll update the configuration details when I have more time for minor tweaks like this.
