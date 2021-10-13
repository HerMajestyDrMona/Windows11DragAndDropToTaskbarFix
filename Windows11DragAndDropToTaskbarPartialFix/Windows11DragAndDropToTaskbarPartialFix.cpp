// Windows11TaskbarDropFiles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <string.h>
#include <chrono>
using namespace std::chrono;

//Basic configuration:
bool PrintDebugInfo = false;
bool ShowConsoleWindowOnStartup = false;
int HowLongLeftMouseButtonPressedBeforeContinueMilliseconds = 1000;
int HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds = 500;
int DefaultSleepPeriodInTheLoopMilliseconds = 500;
int SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds = 50;
int SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds = 10;
int DefaultTaskbarIconWidth = 44;
int DefaultShowDesktopButtonWidth = 20;

int main()
{
	if (!ShowConsoleWindowOnStartup) {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		if (PrintDebugInfo) {
			PrintDebugInfo = false;
		}
	}

	HANDLE handleMutex = CreateMutex(NULL, TRUE, L"MonaWindows11DragToTaskbar-AlreadyRunning");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("Windows11DragAndDropToTaskbarPartialFix is already running. Exiting this instance...\n");
		return 1;
	}

	//Welcome!
	bool HideConsoleWindowSoon = false;
	std::chrono::milliseconds ProgrmStartTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	printf("Windows11DragAndDropToTaskbarPartialFix, ver. 1.0, created by Dr.MonaLisa.\n");
	printf("https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix\n\n");
	if (!PrintDebugInfo) {
		printf("Debug output is disabled, so the console window will be hidden in 5 seconds.\nIn order to terminate this program, please kill \"Windows11DragAndDropToTaskbarPartialFix.exe\" in the Task Manager.\n");
		if (ShowConsoleWindowOnStartup) {
			HideConsoleWindowSoon = true;
		}
	}

	POINT P;
	POINT P_Client;
	char Keyboard_Keys_One_to_Zero[10] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30 };

	//HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	bool CurrentlyLeftMouseButtonIsPressed = false;
	bool DetectedHWNDsForThisMouseClick = false;
	HWND hWndTray = 0;
	HWND hWndRebar = 0;
	HWND hWndMSTaskSwWClass = 0;
	RECT desktop;
	HWND hDesktop = 0;
	int ShowDesktopStartPosition = 0;
	int TaskbarWindowWidth = 0;
	int LastSimulatedHotkeyPressID = -1;
	int PreviousHoveredMouseAppID = -1;
	std::chrono::milliseconds FirstTimeClickedLeftMouseButton = std::chrono::milliseconds(0);
	std::chrono::milliseconds FirstTimeHoveredOverThisAppIcon = std::chrono::milliseconds(0);
	std::chrono::milliseconds TimeNow = std::chrono::milliseconds(0);

	int SleepPeriodNow = DefaultSleepPeriodInTheLoopMilliseconds;

	while (true) {
		if (HideConsoleWindowSoon) {
			TimeNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			if (TimeNow.count() >= (ProgrmStartTime.count() + 5000)) {
				HideConsoleWindowSoon = false;
				ShowWindow(GetConsoleWindow(), SW_HIDE);
			}

		}
		//Check if left mouse button is pressed:
		if (!GetAsyncKeyState(VK_LBUTTON)) {
			if (CurrentlyLeftMouseButtonIsPressed) {
				PreviousHoveredMouseAppID = -1;
				LastSimulatedHotkeyPressID = -1;
				DetectedHWNDsForThisMouseClick = false;
				SleepPeriodNow = DefaultSleepPeriodInTheLoopMilliseconds;
				FirstTimeClickedLeftMouseButton = std::chrono::milliseconds(0);
				CurrentlyLeftMouseButtonIsPressed = false;
			}
			Sleep(SleepPeriodNow);
			continue;
		}
		else {
			TimeNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			if (PrintDebugInfo) {
				std::cout << "Left Mouse Button is pressed. Detecting for how long...\n";
			}
			if (!CurrentlyLeftMouseButtonIsPressed) {
				FirstTimeClickedLeftMouseButton = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			}
			SleepPeriodNow = SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds;
			CurrentlyLeftMouseButtonIsPressed = true;
			if ((FirstTimeClickedLeftMouseButton.count() != 0) && (TimeNow.count() >= (FirstTimeClickedLeftMouseButton.count() + HowLongLeftMouseButtonPressedBeforeContinueMilliseconds))) {
				//Continue:

				if (PrintDebugInfo) {
					std::cout << "Left Mouse Button was pressed for > " << HowLongLeftMouseButtonPressedBeforeContinueMilliseconds << " milliseconds...\n";
				}

				if (!DetectedHWNDsForThisMouseClick) {
					DetectedHWNDsForThisMouseClick = true;
					hWndTray = FindWindow(L"Shell_TrayWnd", nullptr);
					//HWND hWndTrayNotify = FindWindowEx(hWndTray, 0, L"TrayNotifyWnd", nullptr);
					//HWND hWndSysPager = FindWindowEx(hWndTrayNotify, 0, L"SysPager", nullptr);
					//HWND hWndToolbar = FindWindowEx(hWndSysPager, 0, L"ToolbarWindow32", nullptr);
					hWndRebar = FindWindowEx(hWndTray, 0, L"ReBarWindow32", nullptr);
					hWndMSTaskSwWClass = FindWindowEx(hWndRebar, 0, L"MSTaskSwWClass", nullptr);
					//HWND hWndMSTaskListWClass = FindWindowEx(hWndMSTaskSwWClass, 0, L"MSTaskListWClass", nullptr);
					if (PrintDebugInfo) {
						std::cout << "Found Taskbar Window: " << hWndMSTaskSwWClass << "\n";
					}
					RECT rect;
					GetWindowRect(hWndMSTaskSwWClass, &rect);
					//std::cout << "Taskbar Window Rect: " << rect.left << ":" << rect.right << ":" << rect.bottom << ":" << rect.top << "\n";
					TaskbarWindowWidth = rect.right - rect.left;
					if (PrintDebugInfo) {
						std::cout << "Taskbar Window Width: " << TaskbarWindowWidth << "\n";
					}

					int NumberOfItemsOnTaskbar = TaskbarWindowWidth / DefaultTaskbarIconWidth;
					if (PrintDebugInfo) {
						std::cout << "Number of icons on taskbar: " << NumberOfItemsOnTaskbar << "\n";
					}
					hDesktop = GetDesktopWindow();
					GetWindowRect(hDesktop, &desktop);
					ShowDesktopStartPosition = desktop.right - DefaultShowDesktopButtonWidth;
				}
				
				if (hWndMSTaskSwWClass) {

					//Check if taskbar area is visible, not to continue when playing games, etc.
					//if (IsWindowVisible(hWndMSTaskSwWClass)) {
					//if (IsWindowVisible(hWndTray)) {

					//For some reasons IsWindowVisible doesn't work as intended, so let's workaround it:

					GetCursorPos(&P);
					HWND WindowUnderMouse = WindowFromPoint(P);

					if(WindowUnderMouse == hWndMSTaskSwWClass){

						P_Client = P;
						ScreenToClient(hWndMSTaskSwWClass, &P_Client);

						if (PrintDebugInfo) {
							std::cout << "Client Mouse position. X:" << P_Client.x << " Y: " << P_Client.y << "\n";
						}

						//Check if maybe in the "show desktop" area:
						bool ShowDesktopPositionNow = false;
						if (P_Client.y > 0 && P.x >= ShowDesktopStartPosition) {
							ShowDesktopPositionNow = true;
						}

						if ((P_Client.x > 0 && P_Client.y > 0 && P_Client.x <= TaskbarWindowWidth) || ShowDesktopPositionNow) {

							SleepPeriodNow = SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds;

							int CurrentAppIcon = P_Client.x / DefaultTaskbarIconWidth;
							int CurrentAppIconPlusOne = CurrentAppIcon + 1;

							if (ShowDesktopPositionNow) {
								CurrentAppIcon = 999;
								CurrentAppIconPlusOne = 1000;
							}

							if (PreviousHoveredMouseAppID != CurrentAppIcon) {
								PreviousHoveredMouseAppID = CurrentAppIcon;
								FirstTimeHoveredOverThisAppIcon = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
							}

							int HowLongOverThisIconCount = TimeNow.count() - FirstTimeHoveredOverThisAppIcon.count();

							if (PrintDebugInfo) {
								std::cout << "Currently in the taskbar area! App icon ID: " << CurrentAppIconPlusOne << ". Pressed for milliseconds: " << HowLongOverThisIconCount << "\n";
							}

							if (HowLongOverThisIconCount >= HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds) {
								if (CurrentAppIcon != LastSimulatedHotkeyPressID) {
									LastSimulatedHotkeyPressID = CurrentAppIcon;
									if (CurrentAppIcon <= 9) {
										keybd_event(VK_LWIN, MapVirtualKey(VK_LWIN, 0), 0, 0); //Press windows key
										keybd_event(VK_LCONTROL, MapVirtualKey(VK_LCONTROL, 0), 0, 0); //Press CTRL key
										keybd_event(Keyboard_Keys_One_to_Zero[CurrentAppIcon], MapVirtualKey(Keyboard_Keys_One_to_Zero[CurrentAppIcon], 0), 0, 0); //left Press
										Sleep(50);
										keybd_event(Keyboard_Keys_One_to_Zero[CurrentAppIcon], MapVirtualKey(Keyboard_Keys_One_to_Zero[CurrentAppIcon], 0), KEYEVENTF_KEYUP, 0); // left Release
										keybd_event(VK_LCONTROL, MapVirtualKey(VK_LCONTROL, 0), KEYEVENTF_KEYUP, 0); // left Release
										keybd_event(VK_LWIN, MapVirtualKey(VK_LWIN, 0), KEYEVENTF_KEYUP, 0); // left Release
										if (PrintDebugInfo) {
											std::cout << "Simulating Logo Win + " << CurrentAppIconPlusOne << " key\n";
										}

									}
									else if (CurrentAppIcon == 999) {
										HWND hwnd = FindWindow(L"Shell_TrayWnd", NULL);
										if (hwnd) {
											LRESULT res = SendMessage(hwnd, WM_COMMAND, (WPARAM)419, 0);
										}

										//Show desktop thing:

										/*keybd_event(VK_LWIN, MapVirtualKey(VK_LWIN, 0), 0, 0); //Press windows key
										keybd_event(0x44, MapVirtualKey(0x44, 0), 0, 0); //left Press
										Sleep(50);
										keybd_event(0x44, MapVirtualKey(0x44, 0), KEYEVENTF_KEYUP, 0); // left Release
										keybd_event(VK_LWIN, MapVirtualKey(VK_LWIN, 0), KEYEVENTF_KEYUP, 0); // left Release*/

										if (PrintDebugInfo) {
											std::cout << "Simulating Logo Win + " << CurrentAppIconPlusOne << " key\n";
										}
									}
									else {
										if (PrintDebugInfo) {
											std::cout << "Unfortunately, can't restore the window because App icon ID is greater than 10 :(\n";
										}
									}
								}
							}
						}
						else {
							SleepPeriodNow = SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds;
						}
					}
				}
			}
		}

		Sleep(SleepPeriodNow);
	}
}
