## **Custom Configuration**

It's possible to configure the program by creating a configuration file at the same location as `Windows11DragAndDropToTaskbarFix.exe`. The configuration file should be named: `Windows11DragAndDropToTaskbarFixConfig.txt`. You can automate this process by clicking on the Mona Lisa Megan Fox `Tray icon` and then `Configure...` from the menu. It will create the correct file and open this GitHub page for reference.

When you modify `Windows11DragAndDropToTaskbarFixConfig.txt`, the program will ask you to automatically restart itself. So you don't need to manually restart it each time you want to test something.

You don't need to add all variables to your configuration file. Please only add the ones you need. The program will use the same default values as present after `Variable=Value` listed below.

You can include the following variables to your `Windows11DragAndDropToTaskbarFixConfig.txt` file:

### General Options

#### Should the program run automatically on system startup?
- 1 = YES. The program will create the `HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run\Windows11DragAndDropToTaskbarFix` registry key.
- 0 = NO. The program will delete the existing autorun registry key if it exists.
```
AutomaticallyRunThisProgramOnStartup=0
```

#### Should the program start as administrator?
- 1 = YES. The program will check if the current instance is elevated. If it isn't, the program will show the UAC prompt asking to start it as administrator.
- 0 = NO. The program will work in the normal mode, but dragging from the other programs that are running as administrator might not work.
```
StartThisProgramAsAdministrator=0
```

#### Should the program show the console window when it starts?
- 1 = YES. A console window will be shown on program start.
- 0 = NO. The program will start invisibly and no extra window will pop-up.
```
ShowConsoleWindowOnStartup=0
```

#### Should the program print the debug information?
- 1 = YES. If `ShowConsoleWindowOnStartup=1` the program will print a lot of messages about the actions done.
- 0 = NO. The program won't show any debug information and run as fast as possible (recommended).
```
PrintDebugInfo=0
```

#### Should the program use a fix for an issue where sometimes incorrect icons are hovered on the taskbar? This bug usually occurs after the computer wakes up from Sleep Mode, connecting or disconnecting secondary screens, or plugging out the laptop charger. The fix opens the self-created window for around 100 milliseconds, forcing the taskbar window to update and return the correct `RECT`.
- 1 = YES (recommended).
- 0 = NO. It's a high chance that you will experience the issue mentioned above.
```
UseFixForBugAfterSleepMode=1
```

#### Should the program show the Tray Icon in the system tray?
- 1 = YES. The program will show a Mona Lisa Megan Fox tray icon with options: `Check for updates`, `Read the changelog`, `Configure`, `Open program folder`, `Restart`, `Quit`.
- 0 = No. The tray icon of the program will not be created. You will have to manually kill the `Windows11DragAndDropToTaskbarFix.exe` by the Task Manager in case you want to terminate the program.
```
ShowTrayIcon=1
```

#### Should the program use ver. 1.2.0+ improvements that remove all previous limitations?
- 1 = YES (highly recommended). The program will use the new advanced `Win+T` method that works for all taskbar icons.
- 0 = NO. The program will use the old behaviour where it's limited to the frist 10 icons on the taskbar and is generally bad.
```
UseTheNewBestMethodEver=1
```

#### Should the program automatically open the first active window under the cursor, except pinned apps with no active window?
- 2 = LIMITED. Open only if no more than 1 window is visible under the icon.
- 1 = ALWAYS. Always open the first window under the icon, even when there are multiple windows under it.
- 0 = NEVER. Never open the first window under the icon, only show the preview thumbnails.

```
AutoOpenFirstWindowInBestMethodEver=2
```

#### Should the program open pinned apps, even when there is no active window? It solves discussion [#37](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/discussions/37).
- 1 = YES. Open programs under the pinned icons, even when they have no active window present.
- 0 = NO. Never open pinned apps with no active window.

```
AutoOpenPinnedAppsEvenWhenNoWindowActive=0
```

#### Should the program check colors of pixels in order to prevent the accidental events when no item is being dragged? It solves issues [#1](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/1) and [#28](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/28).
- 1 = YES. The program will check for a few pixels colors above the mouse pointer on the taskbar. It detects the "incorrect" sign that is shown when something is being dragged over Windows 11 taskbar.
- 0 = NO. The program will not check for pixels colours.

```
DetectKnownPixelColorsToPreventAccidentalEvents=1
```

#### Should the program ignore potentially unwanted drags, for example when the mouse curosr icon is the I-beam? It solves issue [#28](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/28). It is not longer needed in ver. 2.0, because we use a better method.
- 1 = YES. The program will not continue, for example if you're currently selecting a text in the Word document.
- 0 = NO. The program will not check for the mouse cursor icon.

```
IgnorePotentiallyUnwantedDragsFromCertainCursorIcons=0
```

#### For how long (in milliseconds) should the left or the right mouse button be clicked before the program starts checking if the mouse cursor is currently in the task bar area.
```
HowLongLeftMouseButtonPressedBeforeContinueMilliseconds=750
```

#### For how long (in milliseconds) should the mouse cursor be hovered over the same icon on the taskbar in order to restore its window.
```
HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds=200
```

### Options available when `UseTheNewBestMethodEver=1`:

#### Sleep time (in milliseconds) between simulating different keyboard keys.
```
HowLongSleepBetweenDifferentKeysPressMilliseconds=10
```

#### Sleep time (in milliseconds) between simulating the same keyboard keys.
```
HowLongSleepBetweenTheSameKeysPressMilliseconds=0
```

#### Sleep time (in milliseconds) after opening the first window under the icon.
```
HowLongSleepAfterAutoOpenFirstWindowMilliseconds=100
```

#### Sleep time (in milliseconds) after opening pinned apps (only used when option `AutoOpenPinnedAppsEvenWhenNoWindowActive` is `1`).
```
HowLongSleepAfterOpeningPinnedAppMilliseconds=500
```

#### Delay (in milliseconds) before opening the first window under the icon. Only if `AutoOpenFirstWindowInBestMethodEver` is `2` or `1`.
```
HowLongKeepMouseOverAppIconBeforeAutoOpeningMilliseconds=550
```

#### Timeout (in milliseconds) after which the program interrupts the loop where it's detecting for the preview window changes. It's to avoid opening pinned apps with no active window. It can be a greater value, because it's a non-blocking loop which usually breaks much quicker.
```
PreviewWindowChangeDetectionMaxMilliseconds=1000
```

### Remapping keys used by the program in order to simulate hotkeys
- Since version 1.8 it's possible to configure the program to use different keyboard keys than default ones. It's useful for example in the case described in issue [#17](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/17), where a user manually remapped his keyboard after damaging some of keys with a coffee spill.
- Please read the [Virtual-Key Codes](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) article at docs.microsoft.com to find the right values (0x...).
```
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
```

### Less important options
- You can skip the options below. They're only used to change the main thread sleeping times or default icon sizes.
```
DefaultSleepPeriodInTheLoopMilliseconds=100
SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds=25
SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds=10
DefaultTaskbarIconWidth=44
DefaultTaskbarIconHeight=48
DefaultShowDesktopButtonWidth=20
DefaultSingleWindowPreviewThumbnailWidth=250
DefaultSingleWindowPreviewThumbnailHeight=250
```

#### Should the program monitor file `Windows11DragAndDropToTaskbarFixConfig.txt` for changes?
- 2 = AUTORESTART. When you save changes to the configuration file, the program will automatically restart itself.
- 1 = YES. When you save changes to the configuration file, the program will ask you to restart itself.
- 0 = NO. The program won't check for the configuration file changes.
```
ConfigFileChangeTimeMonitorAllowed=1
```

#### Should the program use an alternative tray icon, modified by QuestYouCraft?
- 1 = YES. A different tray icon with a hand drag gesture will be used.
- 0 = NO. The default Mona Lisa Megan Fox icon will be used.
```
UseAlternativeTrayIcon=0
```

### Questions?
Please feel free to open [#Issues](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues) or [#Discussions](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/discussions) if you have additional questions regarding options behaviour, or if you need help to configure the program on your machine. Please remember that asking questions is not something shameful, it's an advantage showing that you care about customization for your own needs.
