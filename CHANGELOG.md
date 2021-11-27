# Change Log for Windows 11 Drag & Drop to the Taskbar (Fix)
Don't read if you're sensitive to misspellings and grammatical errors.

## [[ver. 1.9.2.1](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v.1.9.2.1-release)]  - 2021-11-27, 14:35 CET
- Added `IgnorePotentiallyUnwantedDragsFromCertainCursorIcons=1` configuration option (enabled by default). It solves issue [#28](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/28).
  - This option blocks potentially unwanted drags, for example when the mouse curosr icon is the I-beam (e.g. selecting a text in the Word document).

## [[ver. 1.9.1.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v.1.9.1.0-release)]  - 2021-11-19, 06:00 CET
- Fixed the program crash (present since version 1.7.0) which could occur when `UseFixForBugAfterSleepMode` was enabled (default), caused by clearing the vector and not pushing updated screen windows to it. It could be identified in Event Viewer by the Application Error offset `000000000000c366` (at least on ver. 1.9).

## [[ver. 1.9.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v.1.9.0.0-release)]  - 2021-11-15, 06:00 CET
- Added `UseAlternativeTrayIcon=0` configuration option that allows you to use the alternative program icon, modified by [QuestYouCraft](https://github.com/QuestYouCraft). Please read [CONFIGURATION](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CONFIGURATION.md) for details.
- When `AutoOpenFirstWindowInBestMethodEver=2` (default), and there is only 1 window under the icon - the program will no longer show the preview window after restoring the app window. This way the program has exactly the same drag & drop behaviour as in previous versions of Windows.
- Clicking `Configure...` from the tray menu will now open your default text editor instead of Windows Notepad.
- Source code: added file `Windows11DragAndDropToTaskbarFix.h`. Moved variables and function definitions to it.
- Some other stability changes.
- Compiled the program using Visual Studio 2022, but kept the `2019 (v142)` toolset, because the program crashed for me a few times when it was compiled with the `2022 (v143) toolset`. Idk why.
- The development process has slowed a bit, because most likely there's nothing left to do. I tried to add the `Drop to Pin` feature, unfortunately there are very limited possibilities and it's impossible to add different files than .exe links. So it's pointless as pinning ordinary files is what users are looking for the most.

## [[ver. 1.8.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v.1.8.0.0-release)]  - 2021-11-02, 07:00 CET
- Added `ShowTrayIcon=1` configuration option that allows you to disable the new Mona Lisa Megan Fox tray icon. Please read [CONFIGURATION](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CONFIGURATION.md) for details. It solves issue [#15](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/15).
- Added a possibility to remap keyboard keys used by the program to simulate hotkeys. Please read [CONFIGURATION](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CONFIGURATION.md) for details. It solves issue [#17](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/17).
- Added `Open program folder...` option to the tray menu, so you can easily find out where your `Windows11DragAndDropToTaskbarFix.exe` is. Useful when you're downloading updates.
- Fixed a bug where the `T` key press was not released when simulated the `Win+T` hotkey.
- Optimized the program by caching the `MapVirtualKey` results. Obviously it won't be noticeable, as the program used less than 0.1% CPU when dragging files.
- Maybe something else that I don't remember. I don't like writing changelog. It's boring and annoying.

## [[ver. 1.7.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v.1.7.0.0-release)]  - 2021-10-31, 17:10 CET
- Happy Halloween.
- Added the taskbar Tray Icon for `Windows 11 Drag & Drop to the Taskbar (Fix)`, identified by the Mona Lisa Megan Fox icon:
  - It's possible to: "Check for updates", "Read the changelog", "Configure", "Restart" and "Quit" the program from the tray icon menu. Most options open the project GitHub pages (the program does not connect to the Internet at any stage).
  - The console window won't longer open by default.
- Added additional checks if the Windows 11 taskbar bug occurred, as discussed in issue [#10](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/10#issuecomment-953005633). The bug causes window `MSTaskSwWClass` to return an incorrect `RECT`. Windows11DragAndDropToTaskbarFix now opens a small self-created window, for ~100 milliseconds in order to force the taskbar update. Please note that this is a Windows 11 bug, not caused by this program.
- Added a new option (enabled by default): `AutoOpenFirstWindowInBestMethodEver=2`. When it's set to 2, the program will not auto-open the first window, if there are 2 or more windows under the same icon. This generally restores exactly the same drag-and-drop behaviour as in previous versions of Windows.
- Probably some other minor improvements.
- The source code still looks awful, sometimes the configuration variable names still make no sense. All this might be improved in the future, but I prefer to focus on important things, especially when we won't need this fix in 1 year (Windows 11 22H2 release).

## [[ver. 1.6.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v.1.6.0.0-release)]  - 2021-10-28, 08:40 CET
- Added support for the right mouse button drag and drop, issue [#14](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/14).
  - *Right-button drag-n-drop is usable when dragging a file and you don't want the default action on drop. E.g. you want to select "Move" from the context menu on mouse button release instead of default "Copy" when dropping file on a folder on the same drive*.

## [[ver. 1.5.1.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v.1.5.1.0-release)]  - 2021-10-27, 20:20 CET
- Fixed an [issue](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/10#issuecomment-953005633) where the program did not work correctly after wake up from the Sleep Mode.
  - The problem was caused by another Windows 11 bug, where often window `MSTaskSwWClass` has incorrect `RECT` after the Sleep Mode.
  - After detecting the bug, the fix starts an empty `CMD.exe` window that auto-disappears, in order to force the taskbar window update. After that `MSTaskSwWClass` returns correct `RECT` again, and `Windows11DragAndDropToTaskbarFix` is able to continue working correctly.
  - The new fix can be disabled by the configuration line: `UseFixForBugAfterSleepMode=0` (but why?).

## [[ver. 1.5.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v.1.5.0.0-release)]  - 2021-10-27, 15:00 CET
- Added support for multiple screens, Issue [#9](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/9).
- Minor optimizations & bug fixes. 

## [[ver. 1.4.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v.1.4.0.0-release)]  - 2021-10-21, 13:00 CET
- Disabled `AutomaticallyRunThisProgramOnStartup` by default. Users can enable it manually, by following the: [CONFIGURATION](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CONFIGURATION.md).
  - It seem to be the main reason of false-positives, according to Virustotal.com.
- Added a new option: `HowLongKeepMouseOverAppIconBeforeAutoOpeningMilliseconds`. Thanks to this, when `AutoOpenFirstWindowInBestMethodEver` is enabled (default), the program will wait before auto opening the first window. It prevents accidental opening of all windows when just moving the cursor with dragged file to the next icon on the taskbar.
- Configuration file: fixed an issue where variables containing a number of milliseconds were not loaded by the program. It's because the function `is_number()` was called with a string containing new line characters, therefore always returning false.
- Compiled the program with Multi-threaded DLL Runtime Library (MD).
  - It reverts the change made in version 1.1.2.0, so executables should have smaller size again.
  - The runtime error: "The procedure entry point __std_tzdb_delete_leap_seconds could not be located in the dynamic link library..." has been fixed by replacing the code which used C++20 standard.
- Added some minor optimizations, but the full optimization will be done in the future.

## [[ver. 1.3.1.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v1.3.1.0-release)]  - 2021-10-19, 13:00 CET
- Fixed an issue where in certain circumstances hotkeys stopped working after restoring the first preview window. For example, the Task Manager window was causing this problem. The fix sets the `Shell_TrayWnd` window as foreground, so hotkeys are activated correctly. It possibly fixes the different reported issues about incorrect position detection.

## [[ver. 1.3.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v1.3.0.0-release)]  - 2021-10-19, 08:30 CET
- Added a new option (enabled by default) `AutoOpenFirstWindowInBestMethodEver=1`:
  - It restores the first window under the hovered app icon, then shows the list of windows again. Works for all icons on the taskbar (not limited to 10).
  - It uses the `ArrowUp` and `Enter` keys simulation to work.
  - It correctly detects if the program under the icon has no window (pinned apps), using another "complicated" method.
- Compiled without unused functions in the code, using `#define DONT_INCLUDE_UNUSED_FUNCTIONS_TO_PREVENT_PSEUDO_ANTIVIRUSES_FROM_THROWING_FALSE_POSITIVES`:
  - Hopefully pseudo-Antiviruses like Kaspersky won't longer trigger false positives. Issue [#5](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/5).
- If you use the configuration file, please remember to restore variables to default, before you test this version. Then tweak it again as you like.

## [[ver. 1.2.1.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v1.2.1.0-release)]  - 2021-10-18, 15:00 CET
- Fixed `ShowConsoleWindowOnStartup` configuration line not working. Issue [#4](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/4).

## [[ver. 1.2.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v1.2.0.0-release)]  - 2021-10-18, 13:25 CET
- Renamed the project from `Windows11DragAndDropToTaskbarPartialFix` to `Windows11DragAndDropToTaskbarFix`. For a good reason!
- Changed the hotkeys working method from `Win+Number` to the advanced `Win+T` method.
- Basically fixed all limitations. I'm not saying it's bug-free, but in my tests everything worked correctly:
  - Multiple windows under the icon are now supported.
  - Pinned apps with no active window will no longer start.
  - And of course: support for all taskbar icons, not limited to 10.
- Traditionally, the code contains a lot of new, unused functions from my tests. Before I found the `Win+T` method, I created some complicated stuff to simulate mouse cursor clicks and switching between windows. It can be vieved under function `Experimental_Workaround_for_buttons_Eleven_Plus()`.
- And probably some other changes that I don't remember now.

## [[ver. 1.1.2.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix/releases/tag/v1.1.2.0-release)]  - 2021-10-16, 19:00 CET
- Fixed issue [#2](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix/issues/2), runtime error: "The procedure entry point __std_tzdb_delete_leap_seconds could not be located in the dynamic link library...":
  - Compiled the program with multithread, static version of the run-time library (MT). It will make the executable size much greater, but I have not much time to investigate this problem more. It's most likely caused by using the C++ 20 standard in function `ReturnConfigFileTime()`.

## [[ver. 1.1.1.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix/releases/tag/v1.1.1.0-release)]  - 2021-10-15, 05:50 CET
- Fixed the high CPU usage problem when moving icons on the taskbar, after update 1.1. It was caused by the missing `Sleep()` before `continue`.

## [[ver. 1.1.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix/releases/tag/v1.1-release)]  - 2021-10-15, 04:55 CET
- Fixed dropping files to the "Show desktop" button (bottom-right of the screen). Seems like it stopped working right before ver 1.0 release when I added an extra check that prevents the program from working when playing games or using full-screen apps.
- Added support for the configuration file `Windows11DragAndDropToTaskbarPartialFixConfig.txt` with auto program restarts when changes are made to the configuration file. Please read [READ ME](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix#readme) for details.
- Added an option allowing to run `Windows11DragAndDropToTaskbarPartialFix.exe` on Windows startup (enabled by default).
- Added the `LowLevelMouseProc` callback, in order to detect the coordinates of the left mouse click instantly. For optimization reasons it's running in a separate thread, because `LowLevelMouseProc` might really slow the mouse movements if the thread it's hooked to has some sleeps or other functions. 
- Partially fixed issue [#1](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix/issues/1). The fix won't activate If the left mouse button was clicked on the taskbar area. It should prevent accidental windows restoration when changing icons positions.
- Reduced the default main loop sleep times a little bit, but it really should have no effects on performance. You can anyway configure these values now.
- Please note that the source code now contains a lot of unused functions. It's because I'm still working on a workaround that would prevent opening programs if their main window can't be found. What I've done now is:
  - Reading .lnk files from `AppData\Roaming\Microsoft\Internet Explorer\Quick Launch\User Pinned\TaskBar` and getting their absolute .exe path.
  - Listing running programs, and getting their PIDs (only if their absolute path matches, so we won't get tricked by processes with the same name).
  - Finding the main window of the PIDs, to know if the fix should activate when hovering the mouse over their icon.
  - Unfortunately, for now that's all I could do. I need to understand the `HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Taskband\Favorites` registry key value to see if it stores the current icon position. Some help would be appreciated!
 - Please note that the source code will be cleaned when there are less serious things to focus on. 

## [[ver. 1.0.0.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix/releases/tag/v1.0-release)] - 2021-10-13, 10:20 CET
- Initial release
- The program detects if you're currently pressing the left mouse button and determines which icon on the taskbar you hover the mouse pointer on. If the cursor stays in the same area for X milliseconds - it simulates the Win+Ctrl+Number hotkey (open the desktop and switch to the last active window of the app pinned to the taskbar in the position indicated by the number), in order to restore the intended window. It also supports dropping files to the "Show desktop" button (bottom-right of the screen).

