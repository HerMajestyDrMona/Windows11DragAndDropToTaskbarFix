#pragma once

#include <iostream>
#include <windows.h>
#include <string.h>
#include <chrono>
#include <Shlobj.h>
#include <filesystem>
#include "shobjidl.h"
#include "shlguid.h"
#include "strsafe.h"
#include <set>
#include <psapi.h>
#include <sstream>
#include <fstream>
#include <shlwapi.h>
#include <regex>
#include <thread>
#include <ole2.h>
#include "resource.h"

#pragma comment(lib, "Shlwapi.lib")
#pragma comment( linker, "/subsystem:windows" )
using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;
#define DONT_INCLUDE_UNUSED_FUNCTIONS_TO_PREVENT_PSEUDO_ANTIVIRUSES_FROM_THROWING_FALSE_POSITIVES 1

//Basic configuration:
bool AutomaticallyRunThisProgramOnStartup = false;
bool ShowConsoleWindowOnStartup = false;
bool PrintDebugInfo = false;
bool UseFixForBugAfterSleepMode = true;
bool ShowTrayIcon = true;
bool UseTheNewBestMethodEver = true;
bool AutoOpenFirstWindowInBestMethodEver = true;
bool AutoOpenFirstWindowInBestMethodEverLimited = true;
bool DetectKnownPixelColorsToPreventAccidentalEvents = true;
bool IgnorePotentiallyUnwantedDragsFromCertainCursorIcons = false;//False since ver 1.10.0.0, because we don't need it with pixels test.
int HowLongSleepBetweenDifferentKeysPressMilliseconds = 20;
int HowLongSleepBetweenTheSameKeysPressMilliseconds = 0;
int HowLongSleepAfterAutoOpenFirstWindowMilliseconds = 100;
int HowLongKeepMouseOverAppIconBeforeAutoOpeningMilliseconds = 550;//So it will open after 200+550 (750 ms as in ver. 1.0)
int PreviewWindowChangeDetectionMaxMilliseconds = 1000;//Keep it higher. It's non-blocking time.

int HowLongLeftMouseButtonPressedBeforeContinueMilliseconds = 750;
int HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds = 200;//750 before.
int DefaultSleepPeriodInTheLoopMilliseconds = 100;
int SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds = 25;
int SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds = 10;
int DefaultTaskbarIconWidth = 44;
int DefaultTaskbarIconHeight = 48;
int DefaultShowDesktopButtonWidth = 20;
int DefaultSingleWindowPreviewThumbnailWidth = 250;
int DefaultSingleWindowPreviewThumbnailHeight = 250;
bool UseAlternativeTrayIcon = false;
//bool KeepConsoleWindowVisibleEvenWhenDebugInfoIsDisabled = false;

bool ConfigFileChangeTimeMonitorAllowed = true;

//Unused (or actually can be used), but not important. Warning, some functions are not longer included in the release
bool UseTheNewWMHOTKEYMethod = true;//Not that reliable method as I thought
bool UseTheNewWorkaroundForButtonsElevenPlus = false;//Not needed. Wasted time on it :(
bool CheckIfPinnedAppsWindowsAreVisible = false;//Not needed. Wasted time on it :(
bool DetectIfFileIsCurrentlyDraggedUsingClipboard = true;//Not working for now
int CheckForNewActiveWindowForButtonsElevenPlusMilliseconds = 2500;//Unused by default
int SleepTimeButtonsElevenPlusMilliseconds = 5;//Unused by default
int AnimationLagButtonsElevenPlusMilliseconds = 100;//Unused by default

//Dynamic variables:
wstring ProgramVersion = L"2.0.0.0";
wstring GitHubConfiguration = L"https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CONFIGURATION.md";
wstring GitHubReleases = L"https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/releases";
wstring GitHubAbout = L"https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix";
wstring GitHubChangeLog = L"https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CHANGELOG.md";
wstring CurrentExeWorks = L"";
wstring CurrentExeWorksFilenameOnly = L"";
wstring CurrentExeWorksPath = L"";

long long int RestartedCrashedTimes = 0;
wstring RestartExtraWstring = L"";
std::time_t NowSettingsChangeTime;
DWORD CurrentProcessID = 0;
bool InterruptMainThread = false;
bool InterruptMouseWatchdogThread = false;
bool InterruptRestartProgram = false;
bool InterruptRestartProgramRunAs = false;

//Virtual Keys Remap:
UINT REMAP_VK_LWIN = VK_LWIN;
UINT REMAP_VK_MENU = VK_MENU;
UINT REMAP_VK_TAB = VK_TAB;
UINT REMAP_VK_LCONTROL = VK_LCONTROL;
UINT REMAP_VK_LSHIFT = VK_LSHIFT;
UINT REMAP_VK_LEFT = VK_LEFT;
UINT REMAP_VK_RIGHT = VK_RIGHT;
UINT REMAP_VK_UP = VK_UP;
UINT REMAP_VK_DOWN = VK_DOWN;
UINT REMAP_VK_RETURN = VK_RETURN;
UINT REMAP_VK_D = 0x44;
UINT REMAP_VK_T = 0x54;
UINT VIRTUAL_REMAP_VK_LWIN = MapVirtualKey(REMAP_VK_LWIN, 0);
UINT VIRTUAL_REMAP_VK_MENU = MapVirtualKey(REMAP_VK_MENU, 0);
UINT VIRTUAL_REMAP_VK_TAB = MapVirtualKey(REMAP_VK_TAB, 0);
UINT VIRTUAL_REMAP_VK_LCONTROL = MapVirtualKey(REMAP_VK_LCONTROL, 0);
UINT VIRTUAL_REMAP_VK_LSHIFT = MapVirtualKey(REMAP_VK_LSHIFT, 0);
UINT VIRTUAL_REMAP_VK_LEFT = MapVirtualKey(REMAP_VK_LEFT, 0);
UINT VIRTUAL_REMAP_VK_RIGHT = MapVirtualKey(REMAP_VK_RIGHT, 0);
UINT VIRTUAL_REMAP_VK_UP = MapVirtualKey(REMAP_VK_UP, 0);
UINT VIRTUAL_REMAP_VK_DOWN = MapVirtualKey(REMAP_VK_DOWN, 0);
UINT VIRTUAL_REMAP_VK_RETURN = MapVirtualKey(REMAP_VK_RETURN, 0);
UINT VIRTUAL_REMAP_VK_D = MapVirtualKey(REMAP_VK_D, 0);
UINT VIRTUAL_REMAP_VK_T = MapVirtualKey(REMAP_VK_T, 0);

//Tray icon Stuff
UINT WM_TASKBAR = 0;
HWND Hwnd;
HMENU Hmenu;
NOTIFYICONDATA notifyIconData;
wchar_t szTIP[64] = L"Windows 11 Drag & Drop to the Taskbar (Fix)";
wchar_t szClassName[] = L"Windows11DragAndDropToTaskbarFix";
wchar_t szTitleName[] = L"Windows 11 Drag & Drop to the Taskbar (Fix)";
wstring ConfigFile = L"Windows11DragAndDropToTaskbarFixConfig.txt";
wstring ConfigFileBase = L"Windows11DragAndDropToTaskbarFixConfig.txt";
wstring ConfigFileAlternative = L"Windows11DragAndDropToTaskbarFixConfig.txt.txt";
wstring ConfigFileAlternative2 = L"Windows11DragAndDropToTaskbarFix.txt";
HINSTANCE hPrevWindow;
HINSTANCE hInstWindow;
int nShowCmdWindow;
HHOOK HandleLowLevelMousePressProc;
bool LeftButtonPressedATM = false;
bool LeftButtonPressedATM_Real = false;
bool RightButtonPressedATM_Real = false;
short Last_Step_Reached = 0;
std::chrono::milliseconds LastTimeClickedLeftMouseButton = std::chrono::milliseconds(0);
std::chrono::milliseconds LastTimeClickedLeftMouseButton_Real = std::chrono::milliseconds(0);
std::chrono::milliseconds LastTimeClickedRightMouseButton_Real = std::chrono::milliseconds(0);
POINT MouseClickStartPoint;
POINT MouseClickStartPoint_Client;
long long int Current_UniqueID_of_the_click = 0;
bool LLMP_Temporarily_Dont_Update_UniqueID = false;
long long int Last_UniqueID_session_of_Experimental_Workaround = -1;
POINT P;
POINT P_Client;
char Keyboard_Keys_One_to_Zero[10] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30 };
const std::vector<std::pair<WPARAM, LPARAM>> New_WM_HOTKEY_Array_LogoWin_CTRL_Num = {
	std::pair<WPARAM, LPARAM> {(WPARAM)0x20F, (LPARAM)0x31000A},
	std::pair<WPARAM, LPARAM> {(WPARAM)0x210, (LPARAM)0x32000A},
	std::pair<WPARAM, LPARAM> {(WPARAM)0x211, (LPARAM)0x33000A},
	std::pair<WPARAM, LPARAM> {(WPARAM)0x212, (LPARAM)0x34000A},
	std::pair<WPARAM, LPARAM> {(WPARAM)0x213, (LPARAM)0x35000A},
	std::pair<WPARAM, LPARAM> {(WPARAM)0x214, (LPARAM)0x36000A},
	std::pair<WPARAM, LPARAM> {(WPARAM)0x215, (LPARAM)0x37000A},
	std::pair<WPARAM, LPARAM> {(WPARAM)0x216, (LPARAM)0x38000A},
	std::pair<WPARAM, LPARAM> {(WPARAM)0x217, (LPARAM)0x39000A},
	std::pair<WPARAM, LPARAM> {(WPARAM)0x218, (LPARAM)0x30000A},
};
bool CurrentlyLeftMouseButtonIsPressed = false;
bool DetectedHWNDsForThisMouseClick = false;
HWND hWndTray = NULL;
HWND hWndTrayNotify = NULL;
HWND hWndRebar = NULL;
HWND hWndMSTaskSwWClass = NULL;
HWND hWndWindowForShowDesktopArea = NULL;
HWND TaskListThumbnailWnd = NULL;
RECT desktop;
HWND hDesktop = NULL;
int ShowDesktopStartPosition = 0;
int TaskbarWindowWidth = 0;
int NumberOfItemsOnTaskbar = 0;
int LastSimulatedHotkeyPressID = -1;
int PreviousHoveredMouseAppID = -1;
std::chrono::milliseconds FirstTimeClickedLeftMouseButton = std::chrono::milliseconds(0);
std::chrono::milliseconds FirstTimeHoveredOverThisAppIcon = std::chrono::milliseconds(0);
std::chrono::milliseconds TimeNow = std::chrono::milliseconds(0);
std::chrono::milliseconds SleepModeFix_Previous_TimeNow = std::chrono::milliseconds(0);
std::chrono::milliseconds LastTimeCheckedForConfigUpdate = std::chrono::milliseconds(0);
time_t LastSettingsChangeTime = 0;
bool CheckedConfigTimeAtLeastOneTime = false;
long long int Previous_UniqueID_of_the_click;
int SleepPeriodNow = DefaultSleepPeriodInTheLoopMilliseconds;
long long Previous_UniqueID_of_the_click_Best_Method_Ever = -1;
int Previous_Button_Number = -1;
int Previous_WindowsScreenSet = -1;
HWND PreviousForegroundWindow;
int JustClickedEnterForBestMethodEver = 0;
RECT rectPreviousTaskListThumbnailWnd;
bool PreviousTaskListThumbnailWndVisible = false;
bool CurrentlyAwaitingForEnterClick = false;
std::chrono::milliseconds AwaitingForEnterClickSince = std::chrono::milliseconds(0);
wchar_t WindowClassName[MAX_PATH];
class windowsHWNDs {
public:
	HWND hWndTray = NULL;
	HWND hWndTrayNotify = NULL;
	HWND hWndRebar = NULL;
	HWND hWndMSTaskSwWClass = NULL;
	HWND TaskListThumbnailWnd = NULL;

};
windowsHWNDs PrimaryScreen;
windowsHWNDs CurrentSecondaryScreen;
std::vector<windowsHWNDs> Array_Windows_by_Screen;
HWND TmpWorkerW = NULL;
HWND TmpTaskList = NULL;
int Current_Mouse_Button_Zero_Left_One_Right = -1;
int Previous_Mouse_Button_Zero_Left_One_Right = -1;
std::wstring Current_Button_Name = L"Unknown";
std::wstring Button_Name_Left = L"Left";
std::wstring Button_Name_Right = L"Right";
std::chrono::milliseconds LastTimeFixedTaskbarSizeBug = std::chrono::milliseconds(0);
long long int TaskbarSizeBugDetectedTimes = 0;
SHELLEXECUTEINFO ShExecInfo = { 0 };
bool ConfigMenuDisabled = false;
int ConfigButtonID = 6;
wstring NameAndVer = L"";
wstring NameAndVer2 = L"";
wstring NameRestart = L"";
MENUITEMINFO	ItemInfo;
bool AllowedCursorIconInThisClick = true;
bool DetectedIconInThisClick = false;
bool DetectedCorrectPixelsInThisClick = false;
int WindowsScreenSet = 0;//Primary
int PreviousDPI_WindowsScreenSet = -1;
long long int Previous_DPI_UniqueID_of_the_click = -1;
double Current_DPI_Scale_X = 1.0;
double Current_DPI_Scale_Y = 1.0;

//Functions:
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void minimize();
void restore();
void InitNotifyIconData();
bool dirExists(const std::wstring& dirName_in);
BOOL FileExistsW(LPCWSTR szPath);
BOOL FileExists(LPCTSTR szPath);
void toUpper(basic_string<char>& s);
void toUpper(basic_string<wchar_t>& s);
void toLower(basic_string<char>& s);
void toLower(basic_string<wchar_t>& s);
string Mona_toUpper(string Input);
wstring Mona_toUpperWs(wstring Input);
string Mona_toLower(string Input);
wstring Mona_toLowerWs(wstring Input);
bool is_number(const std::string& s);
void find_and_replace(string& source, string const& find, string const& replace);
void find_and_replace_ws(wstring& source, wstring const& find, wstring const& replace);
bool NewIsConfigLineEqualTo(string ConfigLine, string SearchFor, string SearchForValue);
long long int NewConfigGetIntValueAfter(string ConfigLine, string SearchFor);
double NewConfigGetDoubleValueAfter(string ConfigLine, string SearchFor);
string trololo(string troll);
bool Mona_Remap_Key(string WhichKey, string ChangeTo, bool DebugPrintNow);
void Mona_Load_Configuration(bool DebugPrintNow);
template <typename TP>
std::time_t to_time_t(TP tp);
std::time_t ReturnConfigFileTime(bool OnlyFirstIf);
bool RegistryGetStringValue(std::wstring& valueBuf, HKEY MainKey, const std::wstring& regSubKey, const std::wstring& regValue);
bool RegistrySetStringValue(HKEY MainKey, const std::wstring& regSubKey, const std::wstring& regValue, const std::wstring& stringToSet);
bool RegistryDeleteKeyValue(HKEY MainKey, const std::wstring& regSubKey, const std::wstring& regValue);
void Check_And_Set_Auto_Program_Startup();
static LRESULT CALLBACK LowLevelMousePressProc(int nCode, WPARAM wParam, LPARAM lParam);
DWORD WINAPI MouseClickWatchdogThread(void* data);
void ResetTmpVariablesFull2();
void ResetTmpVariablesFull();
void ResetTmpVariables();
void NewFunctionToKill(bool ReLaunch);
void Simulate_Show_Desktop_Behaviour();
void Simulate_ALT_Plus_TAB_Hotkey(int SleepFor);
bool Should_Auto_Enter_Now_Question_Mark();
void Check_And_Issue_Auto_Enter_Best_Method_Ever(int ButtonID);
void Finally_The_Best_Method_Ever(int ButtonID, int AllButtonsNumber, int WindowsScreenSet);
static BOOL CALLBACK enumChildWindowCallback_SecondaryTrayWnd(HWND hWnd, LPARAM lparam);
static BOOL CALLBACK enumWindowCallback_SecondaryTrayWnd(HWND hWnd, LPARAM lparam);
bool Fix_Taskbar_Size_Bug(HWND Moomintrollen);
void Update_Primary_Screen_Windows_HWNDSs();
DWORD WINAPI ProgramWindowThread(void* data);
void ClickedOpenPathFromTray();
void ClickedChangelogFromTray();
void ClickedAboutFromTray();
void ClickedCheckForUpdatesFromTray();
void ClickedConfigureFromTray();
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
bool IsCursorIconAllowed();
void AdvancedSleep();
void Update_Pseudo_DPI_Scale();
bool CheckControlPixelsAboveTheMouseOnTaskbar();


#ifndef DONT_INCLUDE_UNUSED_FUNCTIONS_TO_PREVENT_PSEUDO_ANTIVIRUSES_FROM_THROWING_FALSE_POSITIVES
bool AlreadySetAppDataFolders = false;
wstring AppDataFolder = L"";
std::vector<vector<wstring>> Pinned_apps_lnk_to_exe_vector;
//const size_t maxPids = 1024;
const size_t maxPids = 2048;
std::set<std::wstring> processes;
size_t LastBufferSize = 0;
struct handle_data {
	unsigned long process_id;
	HWND best_handle;
};
typedef BOOL(WINAPI* LPQueryFullProcessImageName)(
	HANDLE hProcess, DWORD dwFlags, LPSTR lpExeName, PDWORD lpdwSize);
typedef BOOL(WINAPI* LPQueryFullProcessImageNameW)(
	HANDLE hProcess, DWORD dwFlags, LPWSTR lpExeName, PDWORD lpdwSize);
POINT MouseClickStartPointCopy;
HWND FirstWindowWhereDragged;
bool ItWasDesktopWindow = false;
long long int Unique_ID_of_Click_with_File_Dragged = -1;
long long int Unique_ID_of_Click_with_File_NOT_Dragged = -1;

HRESULT ResolveIt(HWND hwnd, LPCSTR lpszLinkFile, LPWSTR lpszPath, int iPathBufferSize);
void Check_if_Full_Exe_Path_is_currently_running();
vector<wstring> split_ws(const wstring& s, const wstring& delim, const bool keep_empty, std::wstring AddAtTheEnd, std::wstring AddAtTheTop)
inline unsigned int stoui(const std::string& s);
inline unsigned int stouiWs(const std::wstring& s);
BOOL is_main_window(HWND handle);
BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
HWND find_main_window(unsigned long process_id);
BOOL IsProcessRunningPID(DWORD pid);
void Check_if_any_window_from_these_PIDs_is_open();
std::wstring GetBinaryValueFromHKCU(const std::wstring& regSubKey, const std::wstring& regValue);
void Check_Pinned_Apps();
HWND Wait_For_The_New_Active_Window(HWND& ActiveWindowBeforeClickingOnAppIcon, wstring DebugStep);
bool Wait_For_Following_Window_To_Become_Foreground_Under_Mouse(HWND& ActiveWindowBeforeClickingOnAppIcon);
void Experimental_Workaround_for_buttons_Eleven_Plus();
bool Detect_if_Clipboard_Has_Dragged_File_Data();
void TestCall();

#endif