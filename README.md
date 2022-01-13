# Windows 11 Drag & Drop to the Taskbar (Fix)

This program fixes the missing "Drag & Drop to the Taskbar" support in Windows 11. In the best case, such a simple and basic functionality will return to Windows 11 in October 2022 (or never). For now, we have to use workarounds in the OS that was supposed to "empower our productivity".

Windows11DragAndDropToTaskbarFix works with the new Windows 11 taskbar and does not require nasty changes like `UndockingDisabled` or restoration of the `classic taskbar`. It doesn't change any system registry keys (except autostart for itself when manually configured) and does not inject any DLLs to other processes, so it's a very portable solution. This program will not interrupt further windows updates as it doesn't change any system files. It's an independent C++ process that does all the job.

### [Download Binary (Windows11DragAndDropToTaskbarFix.exe)](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/)

### [Install Microsoft Visual C++ 2015-2022 Redistributable x64](https://aka.ms/vs/17/release/vc_redist.x64.exe) 
(in case you're getting the missing `VCRUNTIME140_1.dll` error).

### [Read the Changelog](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CHANGELOG.md)

### [View the source code (Windows11DragAndDropToTaskbarFix.cpp)](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/Windows11DragAndDropToTaskbarFix/Windows11DragAndDropToTaskbarFix.cpp)


## **How Does It Work?**
<a href="https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases/"><img align="right" src="https://user-images.githubusercontent.com/24290461/140068775-473a45f7-1f6a-4b10-8664-e5f8d49440ab.png"></a>

The program detects if you're currently pressing the Left or the Right Mouse Button and determines which icon on the taskbar you hover the mouse pointer on. If the cursor stays in the same area for definied number of milliseconds - it simulates the `Win+T` hotkey and arrow keys in order to restore the intended window, using a quite complicated method. It also supports dropping files to the "Show desktop" button (bottom-right of the screen). The program supports multiple screens, auto startup, and has many configuration options (please read below). Windows11DragAndDropToTaskbarFix has no auto-update function and never connects to the Internet, so you don't need to worry about your privacy.

You can click on the Mona Lisa Megan Fox tray icon to show menu that allows you to `Check for updates`, `Read the changelog`, `Configure`, `Open program folder`, `Restart` and `Quit`.
<br>

## **Custom Configuration: Autostart, Timings, Keys Remapping and more**
It's possible to configure the program by creating a configuration file at the same location as `Windows11DragAndDropToTaskbarFix.exe`. The configuration file should be named: `Windows11DragAndDropToTaskbarFixConfig.txt`. You can automate this process by clicking on the Mona Lisa Megan Fox `Tray icon` and then `Configure...` from the menu. It will create the correct file and open the GitHub page for reference.

Please read a separate article: [CONFIGURATION](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CONFIGURATION.md) for details.


## **Limitations**
- The program does not support pinning apps to the taskbar using the drag and drop gesture, and this feature is currently not planned. However, you still can pin apps to the taskbar by clicking on their icons with the right mouse button, and then "Show more options" -> "Pin to taskbar" from the list. [Example](https://www.thewindowsclub.com/how-to-pin-any-app-to-the-taskbar-in-windows-11).

- If the program does not work for you, and you're using the custom skin modifications / themes, please add the following line to your [configuration file](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CONFIGURATION.md):
```
DetectKnownPixelColorsToPreventAccidentalEvents=0
```

- I'm not aware of any serious limitations in the current version. Please check [#issues](https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues)


## **How to Start or Quit the Program?**

To use the fix, please simply download the binary file above (or compile it yourself) and **start it as any other program**. It works as an independent C++ process.

To quit this program, please click on the Mona Lisa Megan Fox Tray icon, and select "Quit..." from the menu. You can also **kill** `Windows11DragAndDropToTaskbarFix.exe` or `Windows 11 Drag & Drop to the Taskbar (Fix)` **by the Task Manager**.


## Special Thanks To:
<a href="#special-thanks-to"><img align="top" style="margin-right: 1px" height="70px" src="https://user-images.githubusercontent.com/24290461/140594900-93d603d1-4fbc-4865-a211-fcab1de5507d.png"></a>
<a href="#special-thanks-to"><img align="bottom" style="margin-right: 1px" height="70px" src="https://user-images.githubusercontent.com/24290461/141721061-7fcf595f-da2b-4560-b028-0e317e97a7cb.png"></a>

– **Dr. Mona Lisa** for creating this program. Please also check [Unofficial Patch](https://ee2.eu/patch/) for Empire Earth II.
     <br>
– **Martin Morano** for giving permissions to use his awesome "Mona Lisa Megan Fox" artwork, used as the program icon.
     <br>
– **zhongxia_87887** ([veryicon.com](https://www.veryicon.com/icons/system/gesture-series/drag-drop.html)) for providing the free alternative program icon, modified & enhanced by [**QuestYouCraft**](https://github.com/QuestYouCraft).
     <br>
    <br>

## Before / After Videos

Videos recorded thanks to [@Mohammad Suleman](https://www.ilovefreesoftware.com/author/suleman_ilfs) from [ilovefreesoftware.com](https://www.ilovefreesoftware.com/19/windows/how-to-enable-drag-drop-support-in-windows-11-taskbar.html).

Before Windows11DragAndDropToTaskbarFix | After Windows11DragAndDropToTaskbarFix
:-: | :-:
<video src='https://user-images.githubusercontent.com/24290461/140594641-6975cb11-9a1b-434f-a67f-e3cf339366b7.mp4' width=180/> | <video src='https://user-images.githubusercontent.com/24290461/140594643-4f4f01e5-0382-4781-90d6-eafb1d55f361.mp4' width=180/>


### "VCRUNTIME140_1.dll" was not found error
If you get an error saying that "VCRUNTIME140_1.dll" is missing, please install [Microsoft Visual C++ 2015-2022 Redistributable x64](https://aka.ms/vs/17/release/vc_redist.x64.exe). Normally, these runtime libraries are installed by default on Windows 11. If you get this error then you most likely manually removed them before, using "Add or remove programs".

### **Donation?**

If you love this software so much that you would like to buy me a cola, pizza, or anything else - you can make a donation using the button available on my other project's website: [Click here](https://ee2.eu/overview/#donate). Please don't forget to mention in the donation message that it's for this fix, so I can spend it for other things than multiplayer servers for that game :)
