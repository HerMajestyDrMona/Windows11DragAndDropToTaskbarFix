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
#pragma comment(lib, "Shlwapi.lib")
#pragma comment( linker, "/subsystem:windows" )
using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

//Basic configuration:
bool AutomaticallyRunThisProgramOnStartup = true;
bool ShowConsoleWindowOnStartup = true;
bool PrintDebugInfo = false;
bool CheckIfPinnedAppsWindowsAreVisible = true;
int HowLongLeftMouseButtonPressedBeforeContinueMilliseconds = 500;
int HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds = 750;
int DefaultSleepPeriodInTheLoopMilliseconds = 100;
int SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds = 25;
int SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds = 10;
int DefaultTaskbarIconWidth = 44;
int DefaultTaskbarIconHeight = 48;
int DefaultShowDesktopButtonWidth = 20;


//Dynamic variables:

wstring CurrentExeWorks = L"";
wstring CurrentExeWorksFilenameOnly = L"";
wstring CurrentExeWorksPath = L"";

bool dirExists(const std::wstring& dirName_in)
{
	DWORD ftyp = GetFileAttributesW(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

BOOL FileExistsW(LPCWSTR szPath)
{
	/*if (boost::filesystem::exists(szPath)) {
		return true;
	}
	return false;*/

	DWORD dwAttrib = GetFileAttributesW(szPath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL FileExists(LPCTSTR szPath)
{
	/*if (boost::filesystem::exists(szPath)) {
		return true;
	}
	return false;*/

	DWORD dwAttrib = GetFileAttributes(szPath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

// https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s13.html

void toUpper(basic_string<char>& s) {
	for (basic_string<char>::iterator p = s.begin();
		p != s.end(); ++p) {
		*p = toupper(*p); // toupper is for char
	}
}

void toUpper(basic_string<wchar_t>& s) {
	for (basic_string<wchar_t>::iterator p = s.begin();
		p != s.end(); ++p) {
		*p = towupper(*p); // towupper is for wchar_t
	}
}

void toLower(basic_string<char>& s) {
	for (basic_string<char>::iterator p = s.begin();
		p != s.end(); ++p) {
		*p = tolower(*p);
	}
}

void toLower(basic_string<wchar_t>& s) {
	for (basic_string<wchar_t>::iterator p = s.begin();
		p != s.end(); ++p) {
		*p = towlower(*p);
	}
}

string Mona_toUpper(string Input) {
	string s = Input;
	for (basic_string<char>::iterator p = s.begin();
		p != s.end(); ++p) {
		*p = toupper(*p); // toupper is for char
	}
	return s;
}

wstring Mona_toUpperWs(wstring Input) {
	wstring s = Input;
	for (basic_string<wchar_t>::iterator p = s.begin();
		p != s.end(); ++p) {
		*p = towupper(*p); // towupper is for wchar_t
	}
	return s;
}

string Mona_toLower(string Input) {
	string s = Input;
	for (basic_string<char>::iterator p = s.begin();
		p != s.end(); ++p) {
		*p = tolower(*p);
	}
	return s;
}

wstring Mona_toLowerWs(wstring Input) {
	wstring s = Input;
	for (basic_string<wchar_t>::iterator p = s.begin();
		p != s.end(); ++p) {
		*p = towlower(*p);
	}
	return s;
}
bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

//Mona's config loader:

bool NewIsConfigLineEqualTo(string ConfigLine, string SearchFor, string SearchForValue) {
	string SearchForTmp = SearchFor + "=" + SearchForValue;
	std::size_t sssearch1 = ConfigLine.find(SearchForTmp);
	if (sssearch1 != std::string::npos) {
		return true;
	}
	else {
		SearchForTmp = SearchFor + " = " + SearchForValue;
		sssearch1 = ConfigLine.find(SearchForTmp);
		if (sssearch1 != std::string::npos) {
			return true;
		}
		else {
			SearchForTmp = SearchFor + " =" + SearchForValue;
			sssearch1 = ConfigLine.find(SearchForTmp);
			if (sssearch1 != std::string::npos) {
				return true;
			}
			else {
				SearchForTmp = SearchFor + "= " + SearchForValue;
				sssearch1 = ConfigLine.find(SearchForTmp);
				if (sssearch1 != std::string::npos) {
					return true;
				}
			}
		}
	}
	return false;
}

long long int NewConfigGetIntValueAfter(string ConfigLine, string SearchFor) {
	bool GotCorrectString = false;
	string CorrectString = "";
	string SearchForTmp = SearchFor + "=";
	std::size_t sssearch1 = ConfigLine.find(SearchForTmp);
	if (sssearch1 != std::string::npos) {
		CorrectString = ConfigLine.substr(sssearch1 + SearchForTmp.length());
		//MessageBox(Message4, CorrectString.c_str(), "Str Test", MB_OK | MB_ICONERROR);
		GotCorrectString = true;
	}
	else {
		SearchForTmp = SearchFor + " = ";
		sssearch1 = ConfigLine.find(SearchForTmp);
		if (sssearch1 != std::string::npos) {
			CorrectString = ConfigLine.substr(sssearch1 + SearchForTmp.length());
			GotCorrectString = true;
		}
		else {
			SearchForTmp = SearchFor + " =";
			sssearch1 = ConfigLine.find(SearchForTmp);
			if (sssearch1 != std::string::npos) {
				CorrectString = ConfigLine.substr(sssearch1 + SearchForTmp.length());
				GotCorrectString = true;
			}
			else {
				SearchForTmp = SearchFor + "= ";
				sssearch1 = ConfigLine.find(SearchForTmp);
				if (sssearch1 != std::string::npos) {
					CorrectString = ConfigLine.substr(sssearch1 + SearchForTmp.length());
					GotCorrectString = true;
				}
			}
		}
	}

	if (GotCorrectString) {
		//Not needed in this program I guess. Too lazy to use boost in this project.:

		/*find_and_replace(CorrectString, "\r\n", "");
		find_and_replace(CorrectString, "\r", "");
		find_and_replace(CorrectString, "\n", "");*/
		if (CorrectString.length() > 0) {
			if (is_number(CorrectString)) {
				return atoll(CorrectString.c_str());
			}
		}
	}
	return -696969;//Control value
}

double NewConfigGetDoubleValueAfter(string ConfigLine, string SearchFor) {
	bool GotCorrectString = false;
	string CorrectString = "";
	string SearchForTmp = SearchFor + "=";
	std::size_t sssearch1 = ConfigLine.find(SearchForTmp);
	if (sssearch1 != std::string::npos) {
		CorrectString = ConfigLine.substr(sssearch1 + SearchForTmp.length());
		GotCorrectString = true;
	}
	else {
		SearchForTmp = SearchFor + " = ";
		sssearch1 = ConfigLine.find(SearchForTmp);
		if (sssearch1 != std::string::npos) {
			CorrectString = ConfigLine.substr(sssearch1 + SearchForTmp.length());
			GotCorrectString = true;
		}
		else {
			SearchForTmp = SearchFor + " =";
			sssearch1 = ConfigLine.find(SearchForTmp);
			if (sssearch1 != std::string::npos) {
				CorrectString = ConfigLine.substr(sssearch1 + SearchForTmp.length());
				GotCorrectString = true;
			}
			else {
				SearchForTmp = SearchFor + "= ";
				sssearch1 = ConfigLine.find(SearchForTmp);
				if (sssearch1 != std::string::npos) {
					CorrectString = ConfigLine.substr(sssearch1 + SearchForTmp.length());
					GotCorrectString = true;
				}
			}
		}
	}

	if (GotCorrectString) {
		/*find_and_replace(CorrectString, "\r\n", "");
		find_and_replace(CorrectString, "\r", "");
		find_and_replace(CorrectString, "\n", "");*/
		if (CorrectString.length() > 0) {
			//if (is_number(CorrectString)) {
			std::string::size_type sz;     // alias of size_t
			double earth = std::stod(CorrectString, &sz);
			return earth;
			//}
		}
	}
	return -69.69;//Control value
}

//I know people reading the code below will be facepalming, but I don't care. I use the functions which I created when I was 14.

wstring ConfigFile = L"Windows11DragAndDropToTaskbarPartialFixConfig.txt";

void Mona_Load_Configuration() {
	string line = "";
	int rowcnt = 0;
	long long int TmpValueFromNewConfigGetIntFunction = -696969;
	if(FileExists(ConfigFile.c_str())){
	ifstream settingsfile(ConfigFile, ios::binary);
	if (settingsfile.is_open()) {
		while (!settingsfile.eof()) {
			getline(settingsfile, line);
			++rowcnt;
			if (line.length() > 0) {

				if (rowcnt > 1000) {
					//Just in case someone loads a 1000TB file as a config.
					break;
				}


				if (line.length() > 1) {
					string test2 = line.substr(0, 1);
					if (test2 == "/") {
						continue;
					}
					else if (test2 == "#") {
						continue;
					}
					else if (test2 == ";") {
						continue;
					}
					string LastChar = line.substr(line.length() - 1);
					if (LastChar == ";") {
						line = line.substr(0, line.length() - 1);
					}
				}

				if (NewIsConfigLineEqualTo(line, "PrintDebugInfo", "1") || NewIsConfigLineEqualTo(line, "PrintDebugInfo", "true")) {
					PrintDebugInfo = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "PrintDebugInfo", "0") || NewIsConfigLineEqualTo(line, "PrintDebugInfo", "false")) {
					PrintDebugInfo = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "ShowConsoleWindowOnStartup", "1") || NewIsConfigLineEqualTo(line, "ShowConsoleWindowOnStartup", "true")) {
					ShowConsoleWindowOnStartup = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "ShowConsoleWindowOnStartup", "0") || NewIsConfigLineEqualTo(line, "ShowConsoleWindowOnStartup", "false")) {
					ShowConsoleWindowOnStartup = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "CheckIfPinnedAppsWindowsAreVisible", "1") || NewIsConfigLineEqualTo(line, "CheckIfPinnedAppsWindowsAreVisible", "true")) {
					CheckIfPinnedAppsWindowsAreVisible = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "CheckIfPinnedAppsWindowsAreVisible", "0") || NewIsConfigLineEqualTo(line, "CheckIfPinnedAppsWindowsAreVisible", "false")) {
					CheckIfPinnedAppsWindowsAreVisible = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "AutomaticallyRunThisProgramOnStartup", "1") || NewIsConfigLineEqualTo(line, "AutomaticallyRunThisProgramOnStartup", "true")) {
					AutomaticallyRunThisProgramOnStartup = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "AutomaticallyRunThisProgramOnStartup", "0") || NewIsConfigLineEqualTo(line, "AutomaticallyRunThisProgramOnStartup", "false")) {
					AutomaticallyRunThisProgramOnStartup = false;
					continue;
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "HowLongLeftMouseButtonPressedBeforeContinueMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						HowLongLeftMouseButtonPressedBeforeContinueMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}


				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "DefaultSleepPeriodInTheLoopMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						DefaultSleepPeriodInTheLoopMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "DefaultTaskbarIconWidth");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						DefaultTaskbarIconWidth = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "DefaultTaskbarIconHeight");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						DefaultTaskbarIconHeight = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "DefaultShowDesktopButtonWidth");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						DefaultShowDesktopButtonWidth = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}
			}
		}
	}
	}
}


std::time_t ReturnConfigFileTime() {

	if (FileExists(ConfigFile.c_str())) {
		std::filesystem::path FileWithPath(ConfigFile);
		std::filesystem::path full_p = absolute(FileWithPath);
		auto LastWriteTime = std::filesystem::last_write_time(full_p);
		const auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(LastWriteTime);
		const auto time = std::chrono::system_clock::to_time_t(systemTime);
		time_t toreturn = time;
		//MessageBox(Message2, "watchdogs return time", _T("0"), MB_YESNO | MB_ICONQUESTION);
		return toreturn;

	}
	//MessageBox(Message2, "watchdogs return", _T("0"), MB_YESNO | MB_ICONQUESTION);
	return 0;
}


// https://docs.microsoft.com/en-us/windows/win32/shell/links?redirectedfrom=MSDN

HRESULT ResolveIt(HWND hwnd, LPCSTR lpszLinkFile, LPWSTR lpszPath, int iPathBufferSize)
{
	HRESULT hres;
	IShellLink* psl;
	WCHAR szGotPath[MAX_PATH];
	WCHAR szDescription[MAX_PATH];
	WIN32_FIND_DATA wfd;

	*lpszPath = 0; // Assume failure 

	// Get a pointer to the IShellLink interface. It is assumed that CoInitialize
	// has already been called.
	//printf("0\n");
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	if (SUCCEEDED(hres))
	{
		//printf("1\n");
		IPersistFile* ppf;

		// Get a pointer to the IPersistFile interface. 
		hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);

		if (SUCCEEDED(hres))
		{
			//printf("2\n");
			WCHAR wsz[MAX_PATH];

			// Ensure that the string is Unicode. 
			MultiByteToWideChar(CP_ACP, 0, lpszLinkFile, -1, wsz, MAX_PATH);

			// Add code here to check return value from MultiByteWideChar 
			// for success.

			// Load the shortcut. 
			hres = ppf->Load(wsz, STGM_READ);

			if (SUCCEEDED(hres))
			{
				//printf("3\n");
				// Resolve the link. 
				hres = psl->Resolve(hwnd, 0);

				if (SUCCEEDED(hres))
				{
					//printf("4\n");
					// Get the path to the link target. 
					//hres = psl->GetPath(szGotPath, MAX_PATH, (WIN32_FIND_DATA*)&wfd, SLGP_SHORTPATH);
					hres = psl->GetPath(szGotPath, MAX_PATH, (WIN32_FIND_DATA*)&wfd, SLGP_RAWPATH);

					if (SUCCEEDED(hres))
					{
						//printf("5\n");
						// Get the description of the target. 
						hres = psl->GetDescription(szDescription, MAX_PATH);

						if (SUCCEEDED(hres))
						{
							//printf("6\n");
							hres = StringCbCopy(lpszPath, iPathBufferSize, szGotPath);
							if (SUCCEEDED(hres))
							{
								// Handle success
							}
							else
							{
								// Handle the error
							}
						}
					}
				}
			}

			// Release the pointer to the IPersistFile interface. 
			ppf->Release();
		}

		// Release the pointer to the IShellLink interface. 
		psl->Release();
	}
	return hres;
}

bool AlreadySetAppDataFolders = false;
wstring AppDataFolder = L"";

std::vector<vector<wstring>> Pinned_apps_lnk_to_exe_vector;

//const size_t maxPids = 1024;
const size_t maxPids = 2048;
std::set<std::wstring> processes;

typedef BOOL(WINAPI* LPQueryFullProcessImageName)(
	HANDLE hProcess, DWORD dwFlags, LPSTR lpExeName, PDWORD lpdwSize);

typedef BOOL(WINAPI* LPQueryFullProcessImageNameW)(
	HANDLE hProcess, DWORD dwFlags, LPWSTR lpExeName, PDWORD lpdwSize);

void Check_if_Full_Exe_Path_is_currently_running() {
	DWORD pids[maxPids] = {};
	DWORD bytesReturned = 0;
	HMODULE hDLL = LoadLibraryA("kernel32.dll");
	//Now use pointer to get access to functions defined in DLL
	LPQueryFullProcessImageNameW fpQueryFullProcessImageName = (LPQueryFullProcessImageNameW)GetProcAddress(hDLL, "QueryFullProcessImageNameW"); //ANSI version
	if (::EnumProcesses(pids, sizeof pids, &bytesReturned))
	{
		DWORD cProcesses = bytesReturned / sizeof * pids;

		// set SeDebug privilege

		for (DWORD i = 0; i < cProcesses; i++)
		{
			DWORD pid = pids[i];

			if (HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid))
			{
				wchar_t filename[MAX_PATH] = { 0 };
				wchar_t filenamenew[MAX_PATH] = { 0 };
				DWORD charsCarried = MAX_PATH;
				if (fpQueryFullProcessImageName)
				{
					if ((*fpQueryFullProcessImageName)(hProcess, 0, filename, &charsCarried))
					{
						wstring filenamewithpathh = filename;

						//Loop by array of .exes from .lnk:
						if (filenamewithpathh.length() > 2) {
							for (size_t iha = 0; iha < Pinned_apps_lnk_to_exe_vector.size(); iha++) {
								if (Mona_toLowerWs(Pinned_apps_lnk_to_exe_vector[iha][1]) == Mona_toLowerWs(filenamewithpathh)) {
									vector<wstring> CurrentArray = Pinned_apps_lnk_to_exe_vector[iha];
									wstring PIDs = L"";
									if (CurrentArray.size() >= 3) {
										PIDs = CurrentArray[2];
									}
									if (PIDs.length() > 0) {
										PIDs = PIDs + L",";
									}
									PIDs = PIDs + to_wstring(pid);
									if (CurrentArray.size() >= 3) {
										CurrentArray[2] = PIDs;
									}
									else {
										CurrentArray.push_back(PIDs);
									}

									Pinned_apps_lnk_to_exe_vector[iha] = CurrentArray;
									if (PrintDebugInfo) {
										//std::wcout << L"PIDs for Process: " << Pinned_apps_lnk_to_exe_vector[iha][1] << L" Are: " << PIDs << std::endl;
									}
								}
							}
						}

					}
					else
					{
						// handle error
					}


				}
				else {
					//Windows XP, no need code for it here.
				}
				::CloseHandle(hProcess);
			}
		}
	}
}

vector<wstring> split_ws(const wstring& s, const wstring& delim, const bool keep_empty = true, std::wstring AddAtTheEnd = L"", std::wstring AddAtTheTop = L"") {
	vector<wstring> result;
	if (delim.empty()) {
		result.push_back(s);
		return result;
	}
	wstring::const_iterator substart = s.begin(), subend;
	while (true) {
		subend = search(substart, s.end(), delim.begin(), delim.end());
		wstring temp(substart, subend);
		if (keep_empty || !temp.empty()) {
			//std::wcout << "temp: " << temp << std::endl;
			if (AddAtTheEnd.length() > 0) {
				wstring temp2 = temp + AddAtTheEnd;
				result.push_back(temp2);
			}
			else if (AddAtTheTop.length() > 0) {
				wstring temp2 = AddAtTheTop + temp;
				result.push_back(temp2);
			}
			else {
				result.push_back(temp);
			}
		}
		if (subend == s.end()) {
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}

inline unsigned int stoui(const std::string& s)
{
	std::istringstream reader(s);
	unsigned int val = 0;
	reader >> val;
	return val;
}

inline unsigned int stouiWs(const std::wstring& s)
{
	std::wistringstream reader(s);
	unsigned int val = 0;
	reader >> val;
	return val;
}

struct handle_data {
	unsigned long process_id;
	HWND best_handle;
};


BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !is_main_window(handle)) {
		return TRUE;
	}
	data.best_handle = handle;
	return FALSE;
}

HWND find_main_window(unsigned long process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.best_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.best_handle;
}

BOOL IsProcessRunningPID(DWORD pid)
{
	HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
	DWORD ret = WaitForSingleObject(process, 0);
	CloseHandle(process);
	return ret == WAIT_TIMEOUT;
}


void Check_if_any_window_from_these_PIDs_is_open() {
	for (size_t iha = 0; iha < Pinned_apps_lnk_to_exe_vector.size(); iha++) {
			wstring PIDsFound = L"";
			vector<wstring> PiDs_Array;
			if (Pinned_apps_lnk_to_exe_vector[iha].size() >= 3) {
				PIDsFound = Pinned_apps_lnk_to_exe_vector[iha][2];
			}
			if (PIDsFound.length() > 0) {
				PiDs_Array = split_ws(PIDsFound, L",", false);
			}
			//std::wcout << "PIDsFound: " << Pinned_apps_lnk_to_exe_vector[iha][1] << L". PIDs: " << PIDsFound << "Array size: " << PiDs_Array.size() << std::endl;

			if (PiDs_Array.size() > 0) {
				for (size_t iha2 = 0; iha2 < PiDs_Array.size(); iha2++) {
					DWORD NicePID = stouiWs(PiDs_Array[iha2]);
					//std::wcout << "NicePID: " << Pinned_apps_lnk_to_exe_vector[iha][1] << L". PID: " << NicePID << std::endl;
					if (NicePID > 0) {
						if (IsProcessRunningPID(NicePID)) {
							//std::wcout << "Process is running: " << Pinned_apps_lnk_to_exe_vector[iha][1] << L". PID: " << NicePID << std::endl;
							HWND MainWindow = find_main_window(NicePID);
							if (MainWindow) {
								vector<wstring> CurrentVector = Pinned_apps_lnk_to_exe_vector[iha];
								wstring AtLeastOneHWNDFound = L"true";
								if (CurrentVector.size() >= 4) {
									CurrentVector[3] = AtLeastOneHWNDFound;
								}
								else {
									CurrentVector.push_back(AtLeastOneHWNDFound);
								}
								//Update vector. Wonder if it's legal on active loop...
								Pinned_apps_lnk_to_exe_vector[iha] = CurrentVector;

								if (PrintDebugInfo) {
									std::wcout << "Found Window For App: " << Pinned_apps_lnk_to_exe_vector[iha][1] << L". PID: " << NicePID << ". HWND: " << MainWindow << std::endl;
								}
							}
							else {
								if (PrintDebugInfo) {
									std::wcout << "Didn't find any window for App: " << Pinned_apps_lnk_to_exe_vector[iha][1] << L". PID: " << NicePID << std::endl;
								}
							}
						}
					}
				}
			}
			
	}
}

bool RegistryGetStringValue(std::wstring &valueBuf, HKEY MainKey, const std::wstring& regSubKey, const std::wstring& regValue)
{
	size_t bufferSize = 0xFFF; // If too small, will be resized down below.
	//std::wstring valueBuf; // Contiguous buffer since C++11.
	valueBuf.resize(bufferSize);
	auto cbData = static_cast<DWORD>(bufferSize * sizeof(wchar_t));
	auto rc = RegGetValueW(
		MainKey,
		regSubKey.c_str(),
		regValue.c_str(),
		RRF_RT_REG_SZ,
		nullptr,
		static_cast<void*>(valueBuf.data()),
		&cbData
	);
	while (rc == ERROR_MORE_DATA)
	{
		// Get a buffer that is big enough.
		cbData /= sizeof(wchar_t);
		if (cbData > static_cast<DWORD>(bufferSize))
		{
			bufferSize = static_cast<size_t>(cbData);
		}
		else
		{
			bufferSize *= 2;
			cbData = static_cast<DWORD>(bufferSize * sizeof(wchar_t));
		}
		valueBuf.resize(bufferSize);
		rc = RegGetValueW(
			MainKey,
			regSubKey.c_str(),
			regValue.c_str(),
			RRF_RT_REG_SZ,
			nullptr,
			static_cast<void*>(valueBuf.data()),
			&cbData
		);
	}
	if (rc == ERROR_SUCCESS)
	{
		cbData /= sizeof(wchar_t);
		valueBuf.resize(static_cast<size_t>(cbData - 1)); // remove end null character
		//return valueBuf;
		return true;
	}
	else
	{
		//throw std::runtime_error("Windows system error code: " + std::to_string(rc));
	}
	return false;
}

bool RegistrySetStringValue(HKEY MainKey, const std::wstring& regSubKey, const std::wstring& regValue, const std::wstring& stringToSet)
{
	auto rc = RegSetKeyValueW(
		MainKey,
		regSubKey.c_str(),
		regValue.c_str(),
		//RRF_RT_REG_SZ,
		REG_SZ,
		stringToSet.c_str(),
		stringToSet.length()*2
	);
	
	if (rc == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		//throw std::runtime_error("Windows system error code: " + std::to_string(rc));
	}

	return false;
}

bool RegistryDeleteKeyValue(HKEY MainKey, const std::wstring& regSubKey, const std::wstring& regValue)
{
	auto rc = RegDeleteKeyValueW(
		MainKey,
		regSubKey.c_str(),
		regValue.c_str()
	);

	if (rc == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		//throw std::runtime_error("Windows system error code: " + std::to_string(rc));
	}

	return false;
}

void Check_And_Set_Auto_Program_Startup() {
	wstring QueryKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	wstring QueryValue = L"Windows11DragAndDropToTaskbarPartialFix";

	bool FoundInRegistry = false;
	bool CorrectInRegistry = false;

	wstring CurrentExeWorksForRegistry = L"\"";
	CurrentExeWorksForRegistry = CurrentExeWorksForRegistry + CurrentExeWorks + L"\"";

	wstring InAutostart = L"";
	if (RegistryGetStringValue(InAutostart, HKEY_CURRENT_USER, QueryKey, QueryValue)) {
		if (InAutostart.length() > 0) {
			FoundInRegistry = true;
			if (CurrentExeWorksForRegistry == InAutostart) {
				CorrectInRegistry = true;
				if (PrintDebugInfo) {
					std::wcout << L"The Auto Startup registry key value is correct. No need to update." << std::endl;
				}
			}
			else {
				std::wcout << L"The existing Auto Startup registry key value: " << InAutostart << L" Length: " << InAutostart.length() << L" does not match the current process: " << CurrentExeWorksForRegistry << L" Length: " << CurrentExeWorksForRegistry.length() << std::endl;
			}
		}
	}
	if (AutomaticallyRunThisProgramOnStartup) {
		if (!FoundInRegistry || !CorrectInRegistry) {
			//Set the key
			if (RegistrySetStringValue(HKEY_CURRENT_USER, QueryKey, QueryValue, CurrentExeWorksForRegistry)) {
				if (PrintDebugInfo) {
					std::wcout << L"Successfully set the Auto Startup registry key value to: " << CurrentExeWorks << std::endl;
				}
			}
			else {
				if (PrintDebugInfo) {
					std::wcout << L"Error setting the Auto Startup registry key value to: " << CurrentExeWorks << std::endl;
				}
			}
		}

	}
	else {
		if (FoundInRegistry) {
			//Delete key
			if (RegistryDeleteKeyValue(HKEY_CURRENT_USER, QueryKey, QueryValue)) {
				if (PrintDebugInfo) {
					std::wcout << L"Successfully removed the Auto Startup registry key value for: " << CurrentExeWorks << std::endl;
				}
			}
			else {
				if (PrintDebugInfo) {
					std::wcout << L"ERROR: Unable to delete the Auto Startup registry key value for: " << CurrentExeWorks << std::endl;
				}
			}
		}
	}
}


size_t LastBufferSize = 0;

std::wstring GetBinaryValueFromHKCU(const std::wstring& regSubKey, const std::wstring& regValue)
{
	LastBufferSize = 0;
	size_t bufferSize = 0xFFF; // If too small, will be resized down below.
	std::wstring valueBuf; // Contiguous buffer since C++11.
	valueBuf.resize(bufferSize);
	auto cbData = static_cast<DWORD>(bufferSize * sizeof(wchar_t));
	auto rc = RegGetValueW(
		HKEY_CURRENT_USER,
		regSubKey.c_str(),
		regValue.c_str(),
		RRF_RT_REG_BINARY,
		nullptr,
		static_cast<void*>(valueBuf.data()),
		&cbData
	);
	while (rc == ERROR_MORE_DATA)
	{
		// Get a buffer that is big enough.
		cbData /= sizeof(wchar_t);
		if (cbData > static_cast<DWORD>(bufferSize))
		{
			bufferSize = static_cast<size_t>(cbData);
		}
		else
		{
			bufferSize *= 2;
			cbData = static_cast<DWORD>(bufferSize * sizeof(wchar_t));
		}
		valueBuf.resize(bufferSize);
		rc = RegGetValueW(
			HKEY_CURRENT_USER,
			regSubKey.c_str(),
			regValue.c_str(),
			RRF_RT_REG_BINARY,
			nullptr,
			static_cast<void*>(valueBuf.data()),
			&cbData
		);
	}
	if (rc == ERROR_SUCCESS)
	{
		cbData /= sizeof(wchar_t);
		valueBuf.resize(static_cast<size_t>(cbData - 1)); // remove end null character
		//std::wcout << L"error success: " << valueBuf << std::endl;
		LastBufferSize = bufferSize;
		return valueBuf;
	}
	else
	{
		//throw std::runtime_error("Windows system error code: " + std::to_string(rc));
	}

	return L"";
}

void Check_Pinned_Apps() {
	//HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Taskband\Favorites
	wstring QueryKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Taskband";
	wstring QueryValue = L"Favorites";

	wstring FavouritesData = GetBinaryValueFromHKCU(QueryKey, QueryValue);
	std::wcout << L"LastBufferSize: " << LastBufferSize << std::endl;
	if (LastBufferSize > 0) {
		std::size_t Test1 = FavouritesData.find(L".lnk",0, LastBufferSize);
		if (Test1 != std::wstring::npos) {
			wstring TestWstr = FavouritesData.substr(Test1);
			std::wcout << L"TestWstr: " << TestWstr << std::endl;
		}

		std::wcout << L"FavouritesData: " << FavouritesData << std::endl;
		//system("pause");
	}

	if (!AlreadySetAppDataFolders) {
		//%AppData%\Microsoft\Internet Explorer\Quick Launch\User Pinned\TaskBar
		wchar_t appdata[MAX_PATH];
		SHGetSpecialFolderPathW(NULL, appdata, CSIDL_APPDATA, 1);
		AppDataFolder = appdata;
		AppDataFolder = AppDataFolder + L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar";
		AlreadySetAppDataFolders = true;
	}
	if (dirExists(AppDataFolder)) {
		//std::wcout << L"Directory Exists: " << AppDataFolder << std::endl;

		Pinned_apps_lnk_to_exe_vector.clear();
		for (const auto& entry : fs::directory_iterator(AppDataFolder)) {
			if (entry.path().extension() == ".lnk") {
				//std::wcout << L"Extension for file is .lnk: " << entry.path() << std::endl;

				//LPWSTR ResolvedLink;
				wchar_t ResolvedLink[MAX_PATH];
				wchar_t ResolvedLinkExpanded[MAX_PATH];

				HRESULT ReadLink = ResolveIt(NULL, entry.path().string().c_str(), ResolvedLink, MAX_PATH);
				if (SUCCEEDED(ReadLink)) {
					ExpandEnvironmentStringsW(ResolvedLink, ResolvedLinkExpanded, MAX_PATH);
					wstring ResolvedLinkWstr = ResolvedLinkExpanded;
					if (ResolvedLinkWstr.length() < 1) {
						if (Mona_toLowerWs(entry.path().filename().wstring()) == L"file explorer.lnk") {
							//std::wcout << L"FILE EXPLORER" << std::endl;
							ResolvedLinkWstr = L"C:\\WINDOWS\\explorer.exe";
						}
					}
					if (ResolvedLinkWstr.length() > 2) {
						std::filesystem::path pp = ResolvedLinkWstr;
						std::filesystem::path pp_absolute = std::filesystem::absolute(ResolvedLinkWstr);
						std::filesystem::path p_absolute = std::filesystem::absolute(entry.path());

						if (PrintDebugInfo) {
							std::wcout << "Original: " << ResolvedLink << "Link: " << entry.path() << L" Resolved: " << pp_absolute << std::endl;
						}

						vector<wstring> CurrentAppLinkVector;
						CurrentAppLinkVector.push_back(p_absolute.wstring());
						CurrentAppLinkVector.push_back(pp_absolute.wstring());

						Pinned_apps_lnk_to_exe_vector.push_back(CurrentAppLinkVector);

					}
					else {
						if (PrintDebugInfo) {
							std::wcout << "Couldn't determine path for link: " << entry.path() << L". Resolved: " << ResolvedLinkWstr << std::endl;
						}
					}
				}
				
			}
		}
	}

	//Test
	if (Pinned_apps_lnk_to_exe_vector.size() >= 1) {
		Check_if_Full_Exe_Path_is_currently_running();
		Check_if_any_window_from_these_PIDs_is_open();

		/*for (size_t iha = 0; iha < Pinned_apps_lnk_to_exe_vector.size(); iha++) {
			if (PrintDebugInfo) {
				wstring PIDsFound = L"";
				if (Pinned_apps_lnk_to_exe_vector[iha].size() >= 3) {
					PIDsFound = Pinned_apps_lnk_to_exe_vector[iha][2];
				}
				std::wcout << "Test App Link: " << Pinned_apps_lnk_to_exe_vector[iha][0] << L". Resolved: " << Pinned_apps_lnk_to_exe_vector[iha][1] << ". PIDs: " << PIDsFound << std::endl;
			}
		}*/
	}
}

HHOOK HandleLowLevelMousePressProc;
bool LeftButtonPressedATM = false;
std::chrono::milliseconds LastTimeClickedLeftMouseButton = std::chrono::milliseconds(0);
POINT MouseClickStartPoint;
POINT MouseClickStartPoint_Client;
long long int Current_UniqueID_of_the_click = 0;

//Important: This Callback can slow down mouse move of the system!!! Don't put anything unnecessary here, and use the other thread!
static LRESULT CALLBACK LowLevelMousePressProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION) {

		if (wParam == WM_LBUTTONDOWN)
		{
			LeftButtonPressedATM = true;
			LastTimeClickedLeftMouseButton = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			GetCursorPos(&MouseClickStartPoint);
			Current_UniqueID_of_the_click++;
		}

		else if (wParam == WM_LBUTTONUP)
		{
			LeftButtonPressedATM = false;
		}
	}
	return CallNextHookEx(HandleLowLevelMousePressProc, nCode, wParam, lParam);
}

DWORD WINAPI MouseClickWatchdogThread(void* data) {
	
	HINSTANCE hInstLowLevelMousePressProc = GetModuleHandle(NULL);
	HandleLowLevelMousePressProc = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMousePressProc, hInstLowLevelMousePressProc, 0);
	MSG msgMouseClickWatchdog;
	while (GetMessage(&msgMouseClickWatchdog, 0, 0, 0))
	{
		PeekMessage(&msgMouseClickWatchdog, 0, 0, 0, 0x0001);
	}
	UnhookWindowsHookEx(HandleLowLevelMousePressProc);
	return 0;
}

POINT P;
POINT P_Client;
char Keyboard_Keys_One_to_Zero[10] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30 };

bool CurrentlyLeftMouseButtonIsPressed = false;
bool DetectedHWNDsForThisMouseClick = false;
HWND hWndTray = 0;
HWND hWndTrayNotify = 0;
HWND hWndRebar = 0;
HWND hWndMSTaskSwWClass = 0;
HWND hWndWindowForShowDesktopArea = 0;
RECT desktop;
HWND hDesktop = 0;
int ShowDesktopStartPosition = 0;
int TaskbarWindowWidth = 0;
int LastSimulatedHotkeyPressID = -1;
int PreviousHoveredMouseAppID = -1;
std::chrono::milliseconds FirstTimeClickedLeftMouseButton = std::chrono::milliseconds(0);
std::chrono::milliseconds FirstTimeHoveredOverThisAppIcon = std::chrono::milliseconds(0);
std::chrono::milliseconds TimeNow = std::chrono::milliseconds(0);
std::chrono::milliseconds LastTimeCheckedForConfigUpdate = std::chrono::milliseconds(0);
time_t LastSettingsChangeTime = 0;
bool CheckedConfigTimeAtLeastOneTime = false;

long long int Previous_UniqueID_of_the_click;

int SleepPeriodNow = DefaultSleepPeriodInTheLoopMilliseconds;

void ResetTmpVariables() {
	PreviousHoveredMouseAppID = -1;
	LastSimulatedHotkeyPressID = -1;
	DetectedHWNDsForThisMouseClick = false;
	SleepPeriodNow = DefaultSleepPeriodInTheLoopMilliseconds;
	FirstTimeClickedLeftMouseButton = std::chrono::milliseconds(0);
}

void find_and_replace(string& source, string const& find, string const& replace)
{
	//boost::replace_all(source, find, replace);
	for (std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
	{
	source.replace(i, find.length(), replace);
	i += replace.length() - find.length() + 1;
	}
}

void find_and_replace_ws(wstring& source, wstring const& find, wstring const& replace)
{
	//boost::replace_all(source, find, replace);
	for (std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
	{
	source.replace(i, find.length(), replace);
	i += replace.length() - find.length() + 1;
	}
}

void NewFunctionToKill(bool ReLaunch = true) {
	wstring ExeEhe = CurrentExeWorksFilenameOnly;
	wstring ExeEhePath = CurrentExeWorks;

	find_and_replace_ws(ExeEhe, L"\\", L"\\\\");
	find_and_replace_ws(ExeEhePath, L"\\", L"\\\\");

	wstring TaskKill = L"taskkill /F /IM \"" + ExeEhe + L"\"";
	wstring EmptyStringOrWithArgs = L"";

	wstring KillAndLaunch;
	if (ReLaunch) {
		KillAndLaunch = TaskKill + L" & start \"\" \"" + ExeEhePath + L"\" \"killed-restarted" + EmptyStringOrWithArgs + L"\" & exit";
	}
	else {
		KillAndLaunch = TaskKill + L"& exit";
	}

	_wsystem(KillAndLaunch.c_str());
}

int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPWSTR lpCmdLine, int nShowCmd)
{
	//Important to make reading .lnk possible:s
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	wchar_t result[MAX_PATH];
	CurrentExeWorks = std::wstring(result, GetModuleFileNameW(NULL, result, MAX_PATH));
	std::filesystem::path CurrentPath(CurrentExeWorks);
	CurrentExeWorksFilenameOnly = CurrentPath.filename().wstring();
	//std::wcout << CurrentExeWorksFilenameOnly << endl;

	wchar_t CurrentWorkingDirectoryWhereExeIs[MAX_PATH];
	wstring ress = std::wstring(CurrentWorkingDirectoryWhereExeIs, GetModuleFileNameW(NULL, CurrentWorkingDirectoryWhereExeIs, MAX_PATH));
	PathRemoveFileSpecW(CurrentWorkingDirectoryWhereExeIs);
	SetCurrentDirectoryW(CurrentWorkingDirectoryWhereExeIs);
	CurrentExeWorksPath = CurrentWorkingDirectoryWhereExeIs;

	//Test:
	// Unused in ver 1.1. Still working on it :(
	//Check_Pinned_Apps();
	//system("pause");
	if (!ShowConsoleWindowOnStartup) {
		//ShowWindow(GetConsoleWindow(), SW_HIDE);
		if (PrintDebugInfo) {
			PrintDebugInfo = false;
		}
	}
	else {
		AllocConsole();
		FILE* fDummy;
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
	}

	HANDLE handleMutex = CreateMutex(NULL, TRUE, L"MonaWindows11DragToTaskbar-AlreadyRunning");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("Windows11DragAndDropToTaskbarPartialFix is already running. Exiting this instance...\n");
		return 1;
	}

	//Load configuration:
	Mona_Load_Configuration();

	//Welcome!
	bool HideConsoleWindowSoon = false;
	std::chrono::milliseconds ProgrmStartTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	printf("Windows11DragAndDropToTaskbarPartialFix, ver. 1.1.1, created by Dr.MonaLisa.\n");
	printf("https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarPartialFix\n\n");
	printf("You can disable the console window. Please read the GitHub page to learn how to configure this program.\n");
	if (!PrintDebugInfo) {
		printf("Debug output is disabled, so the console window will be hidden in 10 seconds.\nIn order to terminate this program, please kill \"Windows11DragAndDropToTaskbarPartialFix.exe\" in the Task Manager.\n");
		if (ShowConsoleWindowOnStartup) {
			HideConsoleWindowSoon = true;
		}
	}

	//Check auto start:
	Check_And_Set_Auto_Program_Startup();

	//Start Mouse Click Watchdog Thread 
	HANDLE ThreadHandleMouseClickWatchdogThread = CreateThread(NULL, 0, MouseClickWatchdogThread, NULL, 0, NULL);

	bool ConfigFileChangeTimeMonitorAllowed = true;

	while (true) {
		TimeNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		if (HideConsoleWindowSoon) {
			if (TimeNow.count() >= (ProgrmStartTime.count() + 10000)) {
				HideConsoleWindowSoon = false;
				ShowWindow(GetConsoleWindow(), SW_HIDE);
			}
		}
		//Check for config file update:
		if (ConfigFileChangeTimeMonitorAllowed && (TimeNow.count() > LastTimeCheckedForConfigUpdate.count() + 5000)) {
			LastTimeCheckedForConfigUpdate = TimeNow;
			if (FileExists(ConfigFile.c_str())) {
				std::time_t NowSettingsChangeTime = ReturnConfigFileTime();
				if (NowSettingsChangeTime != 0) {
					if (NowSettingsChangeTime > LastSettingsChangeTime) {
						if (CheckedConfigTimeAtLeastOneTime) {
							//File changed, restart the program?
							wstring ReloadChangesTitie = L"Windows11DragAndDropToTaskbarPartialFix.exe by Dr.MonaLisa:";
							wstring ReloadChangesQuestion = L"The configuration file \"";
							ReloadChangesQuestion = ReloadChangesQuestion + ConfigFile;
							ReloadChangesQuestion = ReloadChangesQuestion + L"\" has been modified by another program.\n\nDo you want to restart \"Windows 11 Drag & Drop to the Taskbar (Partial Fix)\" in order to reload settings?\n\n- Click \"YES\" to reload settings from the file\n\n- Click \"NO\" to keep the current settings\n\n- Click \"CANCEL\" to keep the current settings and to not display this warning again";

							int ReloadChangesConfUtx = MessageBoxW(NULL, ReloadChangesQuestion.c_str(), ReloadChangesTitie.c_str(), MB_YESNOCANCEL | MB_ICONEXCLAMATION | MB_TOPMOST | MB_SETFOREGROUND | MB_DEFBUTTON1);
							if (ReloadChangesConfUtx == IDYES) {
								NewFunctionToKill(true);

							}
							else if (ReloadChangesConfUtx == IDNO) {

							}
							else {//Cancel
								ConfigFileChangeTimeMonitorAllowed = false;
							}

						}
					}
					LastSettingsChangeTime = NowSettingsChangeTime;
				}
			}

			CheckedConfigTimeAtLeastOneTime = true;
		}


		//Check if left mouse button is pressed:
		//if (!GetAsyncKeyState(VK_LBUTTON)) {
		//In ver 1.1 we use a new thread
		if(!LeftButtonPressedATM){
			if (CurrentlyLeftMouseButtonIsPressed) {
				ResetTmpVariables();
				CurrentlyLeftMouseButtonIsPressed = false;
			}
		}
		else {
			if (PrintDebugInfo) {
				std::cout << "Left Mouse Button is pressed. Detecting for how long...\n";
			}
			if (!CurrentlyLeftMouseButtonIsPressed) {
				//FirstTimeClickedLeftMouseButton = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
				//In ver 1.1 we use more precise time.
				ResetTmpVariables();
				FirstTimeClickedLeftMouseButton = LastTimeClickedLeftMouseButton;
				Previous_UniqueID_of_the_click = Current_UniqueID_of_the_click;
			}
			else {
				//ver 1.1, so we know if it's the same click as before, without worrying about the thread sleep.
				if (Previous_UniqueID_of_the_click != Current_UniqueID_of_the_click) {
					FirstTimeClickedLeftMouseButton = LastTimeClickedLeftMouseButton;
					Previous_UniqueID_of_the_click = Current_UniqueID_of_the_click;
					if (PrintDebugInfo) {
						std::cout << "Different mouse click unique ID detected: " << Current_UniqueID_of_the_click << ". Resetting...\n";
					}
				}
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
					if (hWndTray) {
						hWndTrayNotify = FindWindowEx(hWndTray, 0, L"TrayNotifyWnd", nullptr);
					}
					else {
						hWndTrayNotify = 0;
					}
					//HWND hWndSysPager = FindWindowEx(hWndTrayNotify, 0, L"SysPager", nullptr);
					//HWND hWndToolbar = FindWindowEx(hWndSysPager, 0, L"ToolbarWindow32", nullptr);
					if (hWndTray) {
						hWndRebar = FindWindowEx(hWndTray, 0, L"ReBarWindow32", nullptr);
					}
					else {
						hWndRebar = 0;
					}
					if (hWndRebar) {
						hWndMSTaskSwWClass = FindWindowEx(hWndRebar, 0, L"MSTaskSwWClass", nullptr);
					}
					else {
						hWndMSTaskSwWClass = 0;
					}

					//1.1 fix, actually not needed, it uses hWndTrayNotify HWND.
					/*if (hWndTrayNotify) {
						hWndWindowForShowDesktopArea = FindWindowEx(hWndTrayNotify, 0, L"Windows.UI.Composition.DesktopWindowContentBridge", nullptr);
					}
					else {
						hWndWindowForShowDesktopArea = 0;
					}*/

					std::cout << "Found hWndWindowForShowDesktopArea Window: " << hWndWindowForShowDesktopArea << "\n";

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

					if(WindowUnderMouse == hWndMSTaskSwWClass || WindowUnderMouse == hWndTrayNotify){

						P_Client = P;
						ScreenToClient(hWndMSTaskSwWClass, &P_Client);
		
						MouseClickStartPoint_Client = MouseClickStartPoint;
						ScreenToClient(hWndMSTaskSwWClass, &MouseClickStartPoint_Client);

						//Check if user clicked the left mouse button in the taskbar area, so should not continue:
						//std::cout << "Left Mouse Click Started in:" << MouseClickStartPoint.x << " Y: " << MouseClickStartPoint.y << "\n";

						if (MouseClickStartPoint_Client.x >= 0 && MouseClickStartPoint_Client.y >= 0) {
							if (PrintDebugInfo) {
								std::cout << "Left Mouse Click Started in the taskbar area: X: " << MouseClickStartPoint_Client.x << " Y: " << MouseClickStartPoint_Client.y << ", so skipping.\n";
							}
							//The sleep was missing there causing heavy CPU usage. Fixed in ver 1.1.1
							Sleep(SleepPeriodNow);
							continue;
						}

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
