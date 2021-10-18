# Change Log for Windows 11 Drag & Drop to the Taskbar (Fix)
Don't read if you're sensitive to misspellings and grammatical errors.

## [[ver. 1.2.1.0](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/tag/v1.2.1.0-release)]  - 2021-10-18, 15:00 CET
- Fixed `ShowConsoleWindowOnStartup` configuration line not working.

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

