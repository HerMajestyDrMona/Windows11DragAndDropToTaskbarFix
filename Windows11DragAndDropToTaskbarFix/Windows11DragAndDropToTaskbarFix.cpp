#include "Windows11DragAndDropToTaskbarFix.h"

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

std::wstring s2ws(const std::string& s)
{
	/*int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;*/

	//to get rid of c++17 warnings
	//UINT codePage = CP_THREAD_ACP;
	UINT codePage = CP_UTF8;
	if (s.empty())
	{
		return std::wstring();
	}

	int required = ::MultiByteToWideChar(codePage, 0, s.data(), (int)s.size(), NULL, 0);
	if (0 == required)
	{
		return std::wstring();
	}

	std::wstring str2;
	str2.resize(required);

	int converted = ::MultiByteToWideChar(codePage, 0, s.data(), (int)s.size(), &str2[0], str2.capacity());
	if (0 == converted)
	{
		return std::wstring();
	}

	return str2;
}

string ws2s(const std::wstring& wstr)
{
	/*typedef std::codecvt_utf8<wchar_t> convert_typeX;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);*/

	//other:
	/*std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.to_bytes(wstr);*/


	//to get rid of c++17 warnings
	//https://gist.github.com/vurdalakov/29d05d1820a241e3ba482ceaf28af2de

	//UINT codePage = CP_THREAD_ACP;
	UINT codePage = CP_UTF8;
	if (wstr.empty())
	{
		return std::string();
	}

	int required = ::WideCharToMultiByte(codePage, 0, wstr.data(), (int)wstr.size(), NULL, 0, NULL, NULL);
	if (0 == required)
	{
		return std::string();
	}

	std::string str2;
	str2.resize(required);

	int converted = ::WideCharToMultiByte(codePage, 0, wstr.data(), (int)wstr.size(), &str2[0], str2.capacity(), NULL, NULL);
	if (0 == converted)
	{
		return std::string();
	}

	return str2;

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
		find_and_replace(CorrectString, "\r\n", "");
		find_and_replace(CorrectString, "\r", "");
		find_and_replace(CorrectString, "\n", "");
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
		find_and_replace(CorrectString, "\r\n", "");
		find_and_replace(CorrectString, "\r", "");
		find_and_replace(CorrectString, "\n", "");
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
string trololo(string troll) {
	//const char* ca = troll.c_str();
	size_t ca_l = troll.length();
	char* ca2 = new char[ca_l];
	memset(ca2, 0, sizeof(char) * ca_l);
	int ca2_l = 0;
	stringstream ss;
	ss.clear();
	char tmpch[3];
	int tmpchint;
	int tmpch_pos;
	for (size_t i = 0; i < ca_l; ++i) {
		tmpch_pos = i % 2;
		tmpch[tmpch_pos] = troll[i];
		if (tmpch_pos == 1) {
			tmpch[2] = '\0';
			ss << hex << tmpch;
			ss >> tmpchint;
			ca2[ca2_l++] = tmpchint;
			ss.clear();
		}
	}
	string troll2 = string(ca2, ca2_l);
	//delete ca2;
	delete[] ca2;
	return troll2;
}

bool Mona_Remap_Key(string WhichKey, string ChangeTo, bool DebugPrintNow = false) {
	std::size_t CatFelix = ChangeTo.find("0X");//its uppercase
	if (CatFelix != std::string::npos) {
		string MonaKardashian = ChangeTo.substr(CatFelix);
		string KhloeKardashian = ChangeTo.substr(CatFelix + 2);
		if (KhloeKardashian.length() > 0) {
			//string ChaneToHex = trololo(KhloeKardashian);
			//char ChangeToHexChar = ChaneToHex[0];
			UINT ChangeToHexChar = std::stoul(MonaKardashian, nullptr, 16);

			if (WhichKey == "VK_LWIN")
			{
				REMAP_VK_LWIN = ChangeToHexChar;
				VIRTUAL_REMAP_VK_LWIN = MapVirtualKey(REMAP_VK_LWIN, 0);
				return true;
			}
			else if (WhichKey == "VK_MENU")
			{
				REMAP_VK_MENU = ChangeToHexChar;
				VIRTUAL_REMAP_VK_MENU = MapVirtualKey(REMAP_VK_MENU, 0);
				return true;
			}
			else if (WhichKey == "VK_TAB")
			{
				REMAP_VK_TAB = ChangeToHexChar;
				VIRTUAL_REMAP_VK_TAB = MapVirtualKey(REMAP_VK_TAB, 0);
				return true;
			}
			else if (WhichKey == "VK_LCONTROL")
			{
				REMAP_VK_LCONTROL = ChangeToHexChar;
				VIRTUAL_REMAP_VK_LCONTROL = MapVirtualKey(REMAP_VK_LCONTROL, 0);
				return true;
			}
			else if (WhichKey == "VK_LSHIFT")
			{
				REMAP_VK_LSHIFT = ChangeToHexChar;
				VIRTUAL_REMAP_VK_LSHIFT = MapVirtualKey(REMAP_VK_LSHIFT, 0);
				return true;
			}
			else if (WhichKey == "VK_LEFT")
			{
				REMAP_VK_LEFT = ChangeToHexChar;
				VIRTUAL_REMAP_VK_LEFT = MapVirtualKey(REMAP_VK_LEFT, 0);
				return true;
			}
			else if (WhichKey == "VK_RIGHT")
			{
				REMAP_VK_RIGHT = ChangeToHexChar;
				VIRTUAL_REMAP_VK_RIGHT = MapVirtualKey(REMAP_VK_RIGHT, 0);
				return true;
			}
			else if (WhichKey == "VK_UP")
			{
				REMAP_VK_UP = ChangeToHexChar;
				VIRTUAL_REMAP_VK_UP = MapVirtualKey(REMAP_VK_UP, 0);
				return true;
			}
			else if (WhichKey == "VK_DOWN")
			{
				REMAP_VK_DOWN = ChangeToHexChar;
				VIRTUAL_REMAP_VK_DOWN = MapVirtualKey(REMAP_VK_DOWN, 0);
				return true;
			}
			else if (WhichKey == "VK_RETURN")
			{
				REMAP_VK_RETURN = ChangeToHexChar;
				VIRTUAL_REMAP_VK_RETURN = MapVirtualKey(REMAP_VK_RETURN, 0);
				return true;
			}
			else if (WhichKey == "VK_D")
			{
				REMAP_VK_D = ChangeToHexChar;
				VIRTUAL_REMAP_VK_D = MapVirtualKey(REMAP_VK_D, 0);
				return true;
			}
			else if (WhichKey == "VK_T")
			{
				REMAP_VK_T = ChangeToHexChar;
				VIRTUAL_REMAP_VK_T = MapVirtualKey(REMAP_VK_T, 0);
				return true;
			}
		}
	}
	return false;
}

void Mona_Load_Configuration(bool DebugPrintNow = false) {
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
				find_and_replace(line, "\r\n", "");
				find_and_replace(line, "\r", "");
				find_and_replace(line, "\n", "");
				string line_uppercase = Mona_toUpper(line);

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

				//1.8.0 keys remapping:
				std::size_t Angela = line_uppercase.find("REMAP_");
				if (Angela != std::string::npos) {
					string Kamala = line_uppercase.substr(Angela+6);
					std::size_t Joe = Kamala.find(" =");
					string Barack = "";
					if (Joe != std::string::npos) {
						Barack = Kamala.substr(Joe + 2);
					}
					else {
						Joe = Kamala.find("=");
					}
					if (Joe != std::string::npos) {
						Barack = Kamala.substr(Joe + 1);
						Kamala = Kamala.substr(0, Joe);
						if (Kamala.length() > 1) {
							if (Barack.length() > 0) {
								if (Mona_Remap_Key(Kamala, Barack, DebugPrintNow)) {
									if (DebugPrintNow) {
										std::wcout << L"Successfully remaped key: \"" << s2ws(Kamala) << L"\" to: \"" << s2ws(Barack) << L"\". " << std::endl;
									}
								}
								else {
									if (DebugPrintNow) {
										std::wcout << L"Failed to remap key: \"" << s2ws(Kamala) << L"\" to: \"" << s2ws(Barack) << L"\". " << std::endl;
									}
								}
							}
						}
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

				if (NewIsConfigLineEqualTo(line, "UseFixForBugAfterSleepMode", "1") || NewIsConfigLineEqualTo(line, "UseFixForBugAfterSleepMode", "true")) {
					UseFixForBugAfterSleepMode = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "UseFixForBugAfterSleepMode", "0") || NewIsConfigLineEqualTo(line, "UseFixForBugAfterSleepMode", "false")) {
					UseFixForBugAfterSleepMode = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "ShowTrayIcon", "1") || NewIsConfigLineEqualTo(line, "ShowTrayIcon", "true")) {
					ShowTrayIcon = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "ShowTrayIcon", "0") || NewIsConfigLineEqualTo(line, "ShowTrayIcon", "false")) {
					ShowTrayIcon = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "IgnorePotentiallyUnwantedDragsFromCertainCursorIcons", "1") || NewIsConfigLineEqualTo(line, "IgnorePotentiallyUnwantedDragsFromCertainCursorIcons", "true")) {
					IgnorePotentiallyUnwantedDragsFromCertainCursorIcons = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "IgnorePotentiallyUnwantedDragsFromCertainCursorIcons", "0") || NewIsConfigLineEqualTo(line, "IgnorePotentiallyUnwantedDragsFromCertainCursorIcons", "false")) {
					IgnorePotentiallyUnwantedDragsFromCertainCursorIcons = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "UseLowLevelMousePressProcThread", "1") || NewIsConfigLineEqualTo(line, "UseLowLevelMousePressProcThread", "true")) {
					UseLowLevelMousePressProcThread = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "UseLowLevelMousePressProcThread", "0") || NewIsConfigLineEqualTo(line, "UseLowLevelMousePressProcThread", "false")) {
					UseLowLevelMousePressProcThread = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "DetectKnownPixelColorsToPreventAccidentalEvents", "1") || NewIsConfigLineEqualTo(line, "DetectKnownPixelColorsToPreventAccidentalEvents", "true")) {
					DetectKnownPixelColorsToPreventAccidentalEvents = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "DetectKnownPixelColorsToPreventAccidentalEvents", "0") || NewIsConfigLineEqualTo(line, "DetectKnownPixelColorsToPreventAccidentalEvents", "false")) {
					DetectKnownPixelColorsToPreventAccidentalEvents = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "UseAlternativeTrayIcon", "1") || NewIsConfigLineEqualTo(line, "UseAlternativeTrayIcon", "true")) {
					UseAlternativeTrayIcon = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "UseAlternativeTrayIcon", "0") || NewIsConfigLineEqualTo(line, "UseAlternativeTrayIcon", "false")) {
					UseAlternativeTrayIcon = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "StartThisProgramAsAdministrator", "1") || NewIsConfigLineEqualTo(line, "StartThisProgramAsAdministrator", "true")) {
					StartThisProgramAsAdministrator = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "StartThisProgramAsAdministrator", "0") || NewIsConfigLineEqualTo(line, "StartThisProgramAsAdministrator", "false")) {
					StartThisProgramAsAdministrator = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "UseTheNewBestMethodEver", "1") || NewIsConfigLineEqualTo(line, "UseTheNewBestMethodEver", "true")) {
					UseTheNewBestMethodEver = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "UseTheNewBestMethodEver", "0") || NewIsConfigLineEqualTo(line, "UseTheNewBestMethodEver", "false")) {
					UseTheNewBestMethodEver = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "AutoOpenFirstWindowInBestMethodEver", "1") || NewIsConfigLineEqualTo(line, "AutoOpenFirstWindowInBestMethodEver", "true")) {
					AutoOpenFirstWindowInBestMethodEver = true;
					AutoOpenFirstWindowInBestMethodEverLimited = false;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "AutoOpenFirstWindowInBestMethodEver", "2") || NewIsConfigLineEqualTo(line, "AutoOpenFirstWindowInBestMethodEver", "limited")) {
					AutoOpenFirstWindowInBestMethodEver = true;
					AutoOpenFirstWindowInBestMethodEverLimited = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "AutoOpenFirstWindowInBestMethodEver", "0") || NewIsConfigLineEqualTo(line, "AutoOpenFirstWindowInBestMethodEver", "false")) {
					AutoOpenFirstWindowInBestMethodEver = false;
					AutoOpenFirstWindowInBestMethodEverLimited = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "AutoOpenPinnedAppsEvenWhenNoWindowActive", "1") || NewIsConfigLineEqualTo(line, "AutoOpenPinnedAppsEvenWhenNoWindowActive", "true")) {
					AutoOpenPinnedAppsEvenWhenNoWindowActive = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "AutoOpenPinnedAppsEvenWhenNoWindowActive", "0") || NewIsConfigLineEqualTo(line, "AutoOpenPinnedAppsEvenWhenNoWindowActive", "false")) {
					AutoOpenPinnedAppsEvenWhenNoWindowActive = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "ConfigFileChangeTimeMonitorAllowed", "2") || NewIsConfigLineEqualTo(line, "ConfigFileChangeTimeMonitorAllowed", "autorestart")) {
					ConfigFileChangeTimeMonitorAllowed = true;
					ConfigFileChangeTimeMonitorAutoRestart = true;
					continue;
				}
				if (NewIsConfigLineEqualTo(line, "ConfigFileChangeTimeMonitorAllowed", "1") || NewIsConfigLineEqualTo(line, "ConfigFileChangeTimeMonitorAllowed", "true")) {
					ConfigFileChangeTimeMonitorAllowed = true;
					ConfigFileChangeTimeMonitorAutoRestart = false;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "ConfigFileChangeTimeMonitorAllowed", "0") || NewIsConfigLineEqualTo(line, "ConfigFileChangeTimeMonitorAllowed", "false")) {
					ConfigFileChangeTimeMonitorAllowed = false;
					ConfigFileChangeTimeMonitorAutoRestart = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "UseTheNewWMHOTKEYMethod", "1") || NewIsConfigLineEqualTo(line, "UseTheNewWMHOTKEYMethod", "true")) {
					UseTheNewWMHOTKEYMethod = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "UseTheNewWMHOTKEYMethod", "0") || NewIsConfigLineEqualTo(line, "UseTheNewWMHOTKEYMethod", "false")) {
					UseTheNewWMHOTKEYMethod = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "UseTheNewWorkaroundForButtonsElevenPlus", "1") || NewIsConfigLineEqualTo(line, "UseTheNewWorkaroundForButtonsElevenPlus", "true")) {
					UseTheNewWorkaroundForButtonsElevenPlus = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "UseTheNewWorkaroundForButtonsElevenPlus", "0") || NewIsConfigLineEqualTo(line, "UseTheNewWorkaroundForButtonsElevenPlus", "false")) {
					UseTheNewWorkaroundForButtonsElevenPlus = false;
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

				if (NewIsConfigLineEqualTo(line, "FixForBugAfterSleepModeUseOldMethod", "1") || NewIsConfigLineEqualTo(line, "FixForBugAfterSleepModeUseOldMethod", "true")) {
					FixForBugAfterSleepModeUseOldMethod = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "FixForBugAfterSleepModeUseOldMethod", "0") || NewIsConfigLineEqualTo(line, "FixForBugAfterSleepModeUseOldMethod", "false")) {
					FixForBugAfterSleepModeUseOldMethod = false;
					continue;
				}

				if (NewIsConfigLineEqualTo(line, "UseTheNewIconsCountingMethod", "1") || NewIsConfigLineEqualTo(line, "UseTheNewIconsCountingMethod", "true")) {
					UseTheNewIconsCountingMethod = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "UseTheNewIconsCountingMethod", "0") || NewIsConfigLineEqualTo(line, "UseTheNewIconsCountingMethod", "false")) {
					UseTheNewIconsCountingMethod = false;
					continue;
				}

				/*if (NewIsConfigLineEqualTo(line, "AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize", "1") || NewIsConfigLineEqualTo(line, "AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize", "true")) {
					AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize = true;
					continue;
				}
				else if (NewIsConfigLineEqualTo(line, "AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize", "0") || NewIsConfigLineEqualTo(line, "AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize", "false")) {
					AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize = false;
					continue;
				}*/

				/*TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "FixNumberOfIconsOnTaskbarAddOffset");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					FixNumberOfIconsOnTaskbarAddOffset = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
				}*/

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

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "CheckForNewActiveWindowForButtonsElevenPlusMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						CheckForNewActiveWindowForButtonsElevenPlusMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "SleepTimeButtonsElevenPlusMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						SleepTimeButtonsElevenPlusMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "AnimationLagButtonsElevenPlusMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						AnimationLagButtonsElevenPlusMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
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

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "HowLongSleepBetweenTheSameKeysPressMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > -1) {//For performance purposes disallow 0s for now.
						HowLongSleepBetweenTheSameKeysPressMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "HowLongSleepAfterAutoOpenFirstWindowMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > -1) {//For performance purposes disallow 0s for now.
						HowLongSleepAfterAutoOpenFirstWindowMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "HowLongSleepAfterOpeningPinnedAppMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > -1) {//For performance purposes disallow 0s for now.
						HowLongSleepAfterOpeningPinnedAppMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "HowLongKeepMouseOverAppIconBeforeAutoOpeningMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > -1) {//For performance purposes disallow 0s for now.
						HowLongKeepMouseOverAppIconBeforeAutoOpeningMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "PreviewWindowChangeDetectionMaxMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						PreviewWindowChangeDetectionMaxMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "HowLongSleepBetweenDifferentKeysPressMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > -1) {//For performance purposes disallow 0s for now.
						HowLongSleepBetweenDifferentKeysPressMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
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

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "DefaultSingleWindowPreviewThumbnailWidth");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						DefaultSingleWindowPreviewThumbnailWidth = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "DefaultSingleWindowPreviewThumbnailHeight");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						DefaultSingleWindowPreviewThumbnailHeight = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				TmpValueFromNewConfigGetIntFunction = NewConfigGetIntValueAfter(line, "FixForBugAfterSleepModeWindowDisplayTimeMilliseconds");
				if (TmpValueFromNewConfigGetIntFunction != -696969) {
					if (TmpValueFromNewConfigGetIntFunction > 0) {//For performance purposes disallow 0s for now.
						FixForBugAfterSleepModeWindowDisplayTimeMilliseconds = static_cast<int>(TmpValueFromNewConfigGetIntFunction);
						continue;
					}
				}

				//Custom Log file?
				string StringAfterCustomLogFile = "";
				std::size_t findno1 = line.find("CustomLogFile=");
				if (findno1 != std::string::npos) {
					StringAfterCustomLogFile = line.substr(14);
				}
				else {
					std::size_t findno2 = line.find("CustomLogFile = ");
					if (findno2 != std::string::npos) {
						StringAfterCustomLogFile = line.substr(16);
					}
					else {
						std::size_t findno3 = line.find("CustomLogFile =");
						if (findno3 != std::string::npos) {
							StringAfterCustomLogFile = line.substr(15);
						}
					}
				}
				if (StringAfterCustomLogFile.length() > 1) {
					find_and_replace(StringAfterCustomLogFile, "\r\n", "");
					find_and_replace(StringAfterCustomLogFile, "\r", "");
					find_and_replace(StringAfterCustomLogFile, "\n", "");
					if (StringAfterCustomLogFile.length() > 1) {
						HaveCustomLogFile = true;
						CustomLogFile = StringAfterCustomLogFile;
						
					}
				}

			}
		}
	}
	}
}

//https://stackoverflow.com/a/61067330/2517973

template <typename TP>
std::time_t to_time_t(TP tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

std::time_t ReturnConfigFileTime(bool OnlyFirstIf = false) {
	if (FileExists(ConfigFile.c_str())) {
		std::filesystem::path FileWithPath(ConfigFile);
		std::filesystem::path full_p = absolute(FileWithPath);
		auto LastWriteTime = std::filesystem::last_write_time(full_p);

		//We can't use C++20 method for now, because of the "The procedure entry point __std_tzdb_delete_leap_seconds could not be located in the dynamic link library..." error.

		/*const auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(LastWriteTime);
		const auto time = std::chrono::system_clock::to_time_t(systemTime);
		time_t toreturn = time;*/

		//C++17 method:
		time_t toreturn = to_time_t(LastWriteTime);
		return toreturn;

	}
	return 0;
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
	size_t LengthXX = stringToSet.length() * 2;
	auto rc = RegSetKeyValueW(
		MainKey,
		regSubKey.c_str(),
		regValue.c_str(),
		//RRF_RT_REG_SZ,
		REG_SZ,
		stringToSet.c_str(),
		(DWORD)LengthXX
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
	wstring QueryValue = L"Windows11DragAndDropToTaskbarFix";
	wstring QueryValueOld = L"Windows11DragAndDropToTaskbarPartialFix";

	bool FoundInRegistry = false;
	bool CorrectInRegistry = false;

	wstring CurrentExeWorksForRegistry = L"\"";
	CurrentExeWorksForRegistry = CurrentExeWorksForRegistry + CurrentExeWorks + L"\"";

	//Delete old Autostart:
	if (RegistryDeleteKeyValue(HKEY_CURRENT_USER, QueryKey, QueryValueOld)) {
		if (PrintDebugInfo) {
			std::wcout << L"Successfully removed the old executable name Auto Startup registry key value for: " << CurrentExeWorks << std::endl;
		}
	}


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
				if (PrintDebugInfo) {
					std::wcout << L"The existing Auto Startup registry key value: " << InAutostart << L" Length: " << InAutostart.length() << L" does not match the current process: " << CurrentExeWorksForRegistry << L" Length: " << CurrentExeWorksForRegistry.length() << std::endl;
				}
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

//Important: This Callback can slow down mouse move of the system!!! Don't put anything unnecessary here, and use the other thread!
static LRESULT CALLBACK LowLevelMousePressProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION) {

		if (wParam == WM_LBUTTONDOWN)
		{
			LeftButtonPressedATM_Real = true;
			LastTimeClickedLeftMouseButton_Real = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			GetCursorPos(&MouseClickStartPoint);
			if (!LLMP_Temporarily_Dont_Update_UniqueID) {
			Current_UniqueID_of_the_click++;
			}
		}
		else if (wParam == WM_LBUTTONUP)
		{
			LeftButtonPressedATM_Real = false;
			//std::wcout << L"WM_LBUTTONUP was called" << endl;
		}
		if (wParam == WM_RBUTTONDOWN)
		{
			RightButtonPressedATM_Real = true;
			LastTimeClickedRightMouseButton_Real = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			GetCursorPos(&MouseClickStartPoint);
			if (!LLMP_Temporarily_Dont_Update_UniqueID) {
				Current_UniqueID_of_the_click++;
			}
		}
		else if (wParam == WM_RBUTTONUP)
		{
			RightButtonPressedATM_Real = false;
			//std::wcout << L"WM_LBUTTONUP was called" << endl;
		}

	}
	return CallNextHookEx(HandleLowLevelMousePressProc, nCode, wParam, lParam);
}

DWORD WINAPI MouseClickWatchdogThread(void* data) {
	
	milliseconds LowLevelMouseHookThreadStartedTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	HINSTANCE hInstLowLevelMousePressProc = GetModuleHandle(NULL);
	HandleLowLevelMousePressProc = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMousePressProc, hInstLowLevelMousePressProc, 0);
	MSG msgMouseClickWatchdog;
	while (GetMessage(&msgMouseClickWatchdog, 0, 0, 0))
	{
		PeekMessage(&msgMouseClickWatchdog, 0, 0, 0, 0x0001);

		//Maybe no need to check it with every mouse action... It will unhook itself on program exit anyway. 
		/*if (InterruptMouseWatchdogThread) {
			break;
		}*/
	}

	// Not sure if this has any use. If for some reasons Mouse Hook dies restart the program. But will GetMessage get interrupted?...
	if (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() > (LowLevelMouseHookThreadStartedTime.count() + 15000)) {
		//Restart the program, because Mouse Hook got interrupted?
		if (RestartedCrashedTimes < 101) {
			RestartedCrashedTimes++;
			RestartExtraWstring = L"-restarted-times-" + to_wstring(RestartedCrashedTimes) + L"-";
			InterruptMainThread = true;
			InterruptRestartProgram = true;
		}
		else {
			InterruptMainThread = true;
			InterruptRestartProgram = false;
		}
	}

	UnhookWindowsHookEx(HandleLowLevelMousePressProc);
	return 0;
}

//Optimized cleaning, to not write too much memory when not reaching further steps.
void ResetTmpVariablesFull2() {
	CurrentlyAwaitingForEnterClick = false;
	AwaitingForEnterClickSince = std::chrono::milliseconds(0);
	JustClickedEnterForBestMethodEver = 0;
	PreviousTaskListThumbnailWndVisible = false;
	Previous_UniqueID_of_the_click_Best_Method_Ever = -1;
	Previous_Button_Number = -1;
	PreviousHoveredMouseAppID = -1;
	LastSimulatedHotkeyPressID = -1;
}

void ResetTmpVariablesFull() {
	DetectedCorrectPixelsInThisClick = false;
	DetectedHWNDsForThisMouseClick = false;
	FixForBugAfterSleepModeTestedThisLoop = false;
	if (Last_Step_Reached >= 4) {
		ResetTmpVariablesFull2();
	}
}

void ResetTmpVariables() {
	AllowedCursorIconInThisClick = true;
	DetectedIconInThisClick = false;
	SleepPeriodNow = DefaultSleepPeriodInTheLoopMilliseconds;
	FirstTimeClickedLeftMouseButton = std::chrono::milliseconds(0);
	if (Last_Step_Reached >= 2) {
		ResetTmpVariablesFull();
	}
	Last_Step_Reached = 0;
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

void Simulate_Show_Desktop_Behaviour() {
	if (!hWndTray) {
		hWndTray = FindWindow(L"Shell_TrayWnd", nullptr);
	}
	if (hWndTray) {
		LRESULT res = SendMessage(hWndTray, WM_COMMAND, (WPARAM)419, 0);
	}
}

void Simulate_ALT_Plus_TAB_Hotkey(int SleepFor = 50) {
	keybd_event(REMAP_VK_MENU, VIRTUAL_REMAP_VK_MENU, 0, 0); //Press ALT
	keybd_event(REMAP_VK_TAB, VIRTUAL_REMAP_VK_TAB, 0, 0); //Press TAB
	Sleep(SleepFor);
	keybd_event(REMAP_VK_TAB, VIRTUAL_REMAP_VK_TAB, KEYEVENTF_KEYUP, 0); //Release TAB
	keybd_event(REMAP_VK_MENU, VIRTUAL_REMAP_VK_MENU, KEYEVENTF_KEYUP, 0); //Release ALT
}

bool Should_Auto_Enter_Now_Question_Mark() {
	if (CurrentlyAwaitingForEnterClick) {
		if ((AwaitingForEnterClickSince.count() != 0) && (TimeNow.count() >= (AwaitingForEnterClickSince.count() + HowLongKeepMouseOverAppIconBeforeAutoOpeningMilliseconds))) {
			return true;
		}
	}
	return false;
}

void Check_And_Issue_Auto_Enter_Best_Method_Ever(int ButtonID) {
	if (AutoOpenFirstWindowInBestMethodEver) {
		bool AwaitingDoneSimulateEnterNow = false;
		if (HowLongKeepMouseOverAppIconBeforeAutoOpeningMilliseconds > 0) {
			if (CurrentlyAwaitingForEnterClick) {
				if (Should_Auto_Enter_Now_Question_Mark()) {
					AwaitingDoneSimulateEnterNow = true;
				}
			}
			else {
				CurrentlyAwaitingForEnterClick = true;
				AwaitingForEnterClickSince = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			}
		}
		else {
			if (Previous_Button_Number != ButtonID) {
				AwaitingDoneSimulateEnterNow = true;
			}
		}

		//This way we still get the preview window of active apps
		//if (Previous_Button_Number != ButtonID) {
		if (AwaitingDoneSimulateEnterNow){
			CurrentlyAwaitingForEnterClick = false;

			//Sleep to make sure arrow arrive at the location.
			if (HowLongSleepBetweenDifferentKeysPressMilliseconds > 0) {
				Sleep(HowLongSleepBetweenDifferentKeysPressMilliseconds);
			}

			RECT rectAtTheMoment;
			//Yeah, get it in case loop is skipped
			GetWindowRect(TaskListThumbnailWnd, &rectAtTheMoment);

			if (PreviousTaskListThumbnailWndVisible) {
				//Loop to make sure rect change:
				//std::chrono::milliseconds SleepFor(SleepTimeButtonsElevenPlusMilliseconds);
				std::chrono::milliseconds SleepFor(5);
				std::chrono::milliseconds StartedTheLoopAt = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
				long long int StartedTheLoopAtCountPlus = StartedTheLoopAt.count() + PreviewWindowChangeDetectionMaxMilliseconds;

				if (PrintDebugInfo) {
					std::wcout << L"PreviousTaskListThumbnailWndVisible is true. Starting the loop to detect for changes..." << rectPreviousTaskListThumbnailWnd.left << ". After: " << rectAtTheMoment.left << endl;
				}
				std::chrono::milliseconds TimeAtTheLoopNow = std::chrono::milliseconds(0);
				while (IsWindowVisible(TaskListThumbnailWnd)) {
					TimeAtTheLoopNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
					GetWindowRect(TaskListThumbnailWnd, &rectAtTheMoment);
					if (rectAtTheMoment.left != rectPreviousTaskListThumbnailWnd.left) {
						if (PrintDebugInfo) {
							std::wcout << L"Detected TaskListThumbnailWnd rect change. Interrupting the loop. Before: " << rectPreviousTaskListThumbnailWnd.left << ". After: " << rectAtTheMoment.left << endl;
						}
						break;
					}
					if (TimeAtTheLoopNow.count() >= StartedTheLoopAtCountPlus) {
						if (PrintDebugInfo) {
							long long int Difference = TimeAtTheLoopNow.count() - StartedTheLoopAt.count();
							std::wcout << L"The IsWindowVisible() loop timeouted after: " << Difference << L" ms." << endl;
						}
						break;
					}
					std::this_thread::sleep_for(SleepFor);
				}
			}

			rectPreviousTaskListThumbnailWnd = rectAtTheMoment;
			PreviousTaskListThumbnailWndVisible = IsWindowVisible(TaskListThumbnailWnd);
			if (PrintDebugInfo) {
				std::wcout << L"TaskListThumbnailWnd Rect: " << rectAtTheMoment.left << L":" << rectAtTheMoment.right << L":" << rectAtTheMoment.bottom << L":" << rectAtTheMoment.top << L". Window visible bool: " << PreviousTaskListThumbnailWndVisible << "\n";
			}

			//if (IsWindowVisible(TaskListThumbnailWnd)) {
			if (PreviousTaskListThumbnailWndVisible) { //Optimization, not to call IsWindowVisible twice.

				//Count preview window size:
				//1 = 216 175% = 172.
				//2 = 424 150% DPI = 415. 175% = 410.
				//4 = 850
				//5 = 1063.
				//So let's make it... Hmm... < 250.

				int ThumbnailWindowSize = rectAtTheMoment.right - rectAtTheMoment.left;
				int ThumbnailWindowSizeHeight = rectAtTheMoment.bottom - rectAtTheMoment.top;
				if (AutoOpenFirstWindowInBestMethodEverLimited) {
					if (ThumbnailWindowSize > DefaultSingleWindowPreviewThumbnailWidth) {
						if (PrintDebugInfo) {
							std::wcout << "More than 1 windows detected in the Preview Window of Thumbnail. Width: " << ThumbnailWindowSize << ". The ENTER key won't be simulated.\n";
						}
						//Hotfix to prevent hotkeys spam
						JustClickedEnterForBestMethodEver = 2;
						return;
					}
					else if (ThumbnailWindowSizeHeight > DefaultSingleWindowPreviewThumbnailHeight) {
						if (PrintDebugInfo) {
							std::wcout << "List of windows detected on the Preview Window of Thumbnail. Height: " << ThumbnailWindowSizeHeight << ". The ENTER key won't be simulated.\n";
						}
						//Hotfix to prevent hotkeys spam
						JustClickedEnterForBestMethodEver = 2;
						return;
					}
					//1.9.0 = so it will simulate KEY_UP and ENTER, but won't display the preview window again, just like in Win10.
					JustClickedEnterForBestMethodEver = 2;
				}

				//Moved it down in ver. 1.7

				keybd_event(REMAP_VK_UP, VIRTUAL_REMAP_VK_UP, 0, 0);
				if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
					Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
				}
				keybd_event(REMAP_VK_UP, VIRTUAL_REMAP_VK_UP, KEYEVENTF_KEYUP, 0);
				if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
					Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
				}

				//Press UP second time (just in case):
				keybd_event(REMAP_VK_UP, VIRTUAL_REMAP_VK_UP, 0, 0);
				if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
					Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
				}
				keybd_event(REMAP_VK_UP, VIRTUAL_REMAP_VK_UP, KEYEVENTF_KEYUP, 0);

				//Sleep to make sure arrow arrives at the location. should be before IsWindowVisible!
				if (HowLongSleepBetweenDifferentKeysPressMilliseconds > 0) {
					Sleep(HowLongSleepBetweenDifferentKeysPressMilliseconds);
				}

				//Longer sleep
				if (HowLongSleepBetweenDifferentKeysPressMilliseconds > 0) {
					Sleep(HowLongSleepBetweenDifferentKeysPressMilliseconds);
				}

				//Hotfix to prevent hotkeys spam
				if (AutoOpenFirstWindowInBestMethodEverLimited) {
					//Dont display the preview window again if only 1 app was under the icon.
					if (JustClickedEnterForBestMethodEver >= 2) {
						//do nothing
					}
					else {
						JustClickedEnterForBestMethodEver = 1;
					}
				}
				else {
					JustClickedEnterForBestMethodEver = 1;
				}

				if (PrintDebugInfo) {
					std::wcout << L"TaskListThumbnailWnd is visible. Simulating ENTER key..." << endl;
				}

				//Simulate the Space key. It then only opens the active window, not starting apps!!!
				keybd_event(REMAP_VK_RETURN, VIRTUAL_REMAP_VK_RETURN, 0, 0);
				if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
					Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
				}
				keybd_event(REMAP_VK_RETURN, VIRTUAL_REMAP_VK_RETURN, KEYEVENTF_KEYUP, 0);


				//We still need some sleep here, but different than window rect change detection look:
				if (HowLongSleepAfterAutoOpenFirstWindowMilliseconds > 0) {
					Sleep(HowLongSleepAfterAutoOpenFirstWindowMilliseconds);
				}
			}
			else {
				//Check if pinned apps opening is available.
				if (AutoOpenPinnedAppsEvenWhenNoWindowActive) {
					//Hotfix to prevent hotkeys spam
					if (AutoOpenFirstWindowInBestMethodEverLimited) {
						//Dont display the preview window again if only 1 app was under the icon.
						if (JustClickedEnterForBestMethodEver >= 2) {
							//do nothing
						}
						else {
							JustClickedEnterForBestMethodEver = 1;
						}
					}
					else {
						JustClickedEnterForBestMethodEver = 1;
					}

					if (PrintDebugInfo) {
						std::wcout << L"TaskListThumbnailWnd is INVISIBLE, but AutoOpenPinnedAppsEvenWhenNoWindowActive is True, so opening the pinned app." << endl;
					}

					//Longer sleep
					if (HowLongSleepBetweenDifferentKeysPressMilliseconds > 0) {
						Sleep(HowLongSleepBetweenDifferentKeysPressMilliseconds);
					}

					//BUG, sometimes Win+T won't open apps on ENTER press. As workaround we add the old hotkey here for the first 10 icons:
					if (ButtonID <= 10) {
						if (UseTheNewWMHOTKEYMethod && hWndTray) {
							LRESULT SendMessageReturn = SendMessage(hWndTray, WM_HOTKEY, New_WM_HOTKEY_Array_LogoWin_CTRL_Num[ButtonID].first, New_WM_HOTKEY_Array_LogoWin_CTRL_Num[ButtonID].second);
							if (PrintDebugInfo) {
								std::wcout << L"Sending WM_HOTKEY message for Logo Win + CTRL + " << ButtonID << L" key\n";
							}
						}
						else {
							keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, 0, 0); //Press windows key
							keybd_event(REMAP_VK_LCONTROL, VIRTUAL_REMAP_VK_LCONTROL, 0, 0); //Press CTRL key
							keybd_event(Keyboard_Keys_One_to_Zero[ButtonID], MapVirtualKey(Keyboard_Keys_One_to_Zero[ButtonID], 0), 0, 0);
							if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
								Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
							}
							keybd_event(Keyboard_Keys_One_to_Zero[ButtonID], MapVirtualKey(Keyboard_Keys_One_to_Zero[ButtonID], 0), KEYEVENTF_KEYUP, 0);
							keybd_event(REMAP_VK_LCONTROL, VIRTUAL_REMAP_VK_LCONTROL, KEYEVENTF_KEYUP, 0); // left Release
							keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, KEYEVENTF_KEYUP, 0); // left Release
							if (PrintDebugInfo) {
								std::wcout << L"Simulating Logo Win + CTRL + " << ButtonID << L" key\n";
							}
						}
					}
					else {
						//It might not always work due to bug in Windows:

						keybd_event(REMAP_VK_RETURN, VIRTUAL_REMAP_VK_RETURN, 0, 0);
						if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
							Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
						}
						keybd_event(REMAP_VK_RETURN, VIRTUAL_REMAP_VK_RETURN, KEYEVENTF_KEYUP, 0);
					}

					//We still need some sleep here, but different than window rect change detection look:
					if (HowLongSleepAfterOpeningPinnedAppMilliseconds > 0) {
						Sleep(HowLongSleepAfterOpeningPinnedAppMilliseconds);
					}

				}
				else {
					if (PrintDebugInfo) {
						std::wcout << L"TaskListThumbnailWnd is INVISIBLE. Skipping..." << endl;
					}
				}
			}

			//In case preview window changed after clicking ENTER, update the rect and status
			if (IsWindowVisible(TaskListThumbnailWnd)) {
				GetWindowRect(TaskListThumbnailWnd, &rectAtTheMoment);
				rectPreviousTaskListThumbnailWnd = rectAtTheMoment;
				PreviousTaskListThumbnailWndVisible = IsWindowVisible(TaskListThumbnailWnd);
			}

			//Longer sleep again to prevent new keys simulation when window is getting restored
			//No, we must move it to above call
		}
		else {
			if (PrintDebugInfo) {
				std::wcout << L"Button is the same so skipping ENTER." << endl;
			}
		}
	}
}

void Finally_The_Best_Method_Ever(int ButtonID, int AllButtonsNumber, int WindowsScreenSet) {
	HWND CurrentForegroundWindow = GetForegroundWindow();

	bool SameUniqueDragSession = false;
	if (Current_UniqueID_of_the_click == Previous_UniqueID_of_the_click_Best_Method_Ever) {
		if (CurrentForegroundWindow == PreviousForegroundWindow) {
			if (WindowsScreenSet == Previous_WindowsScreenSet) {
				SameUniqueDragSession = true;
			}
		}
		else if (AutoOpenFirstWindowInBestMethodEver) {
			if (JustClickedEnterForBestMethodEver > 0) {
				JustClickedEnterForBestMethodEver++;
			}
			if (JustClickedEnterForBestMethodEver > 1) {
				//No
			}
		}
		else {
			JustClickedEnterForBestMethodEver = 0;
		}
	}
	else {
		JustClickedEnterForBestMethodEver = 0;
	}

	//Reset
	if (Previous_Button_Number != ButtonID || WindowsScreenSet != Previous_WindowsScreenSet) {
		if (HowLongKeepMouseOverAppIconBeforeAutoOpeningMilliseconds > 0) {
			CurrentlyAwaitingForEnterClick = false;
			AwaitingForEnterClickSince = std::chrono::milliseconds(0);
		}
	}

	//Hotfix to not spam the same hotkeys on selected icon
	bool EnterNowAndReturn = false;

	if (Previous_Button_Number == ButtonID) {
		if (PreviousForegroundWindow == hWndTray && CurrentForegroundWindow == hWndTray) {
			if (PrintDebugInfo) {
				std::wcout << "Returning to prevent hotkeys spam..." << endl;
			}
			//ver 1.4
			if (!Should_Auto_Enter_Now_Question_Mark()) {
				return;
			}
			else {
				EnterNowAndReturn = true;
			}
		}
		else if (AutoOpenFirstWindowInBestMethodEver) {
			if (JustClickedEnterForBestMethodEver > 2) {
				if (PrintDebugInfo) {
					std::wcout << "Returning to prevent hotkeys spam after ENTER was clicked..." << endl;
				}
				return;
			}
			else if (JustClickedEnterForBestMethodEver > 0) {
				//Sleep after the previous call, because it just pressed enter, and we didn't want to block that function cus buttons could change.
				//Also IsWindowVisible check would return incorrect value because animation had no time to disappear.

				//EDIT. It can't be in the new call, unfortunately. When button changes and mouse quickly moved to an inactive app icon, it would open it:
				/*if (HowLongSleepAfterAutoOpenFirstWindowMilliseconds > 0) {
					Sleep(HowLongSleepAfterAutoOpenFirstWindowMilliseconds);
				}*/
			}
		}
		if (EnterNowAndReturn) {
			if (PrintDebugInfo) {
				std::wcout << L"Simulating ENTER now (if enabled), after timeout." << endl;
			}
			Check_And_Issue_Auto_Enter_Best_Method_Ever(ButtonID);
			return;
		}
	}

	//Hotfix, because this window will get focus when hotkey is pressed
	if (!SameUniqueDragSession) {
		if (CurrentForegroundWindow != hWndTray) {
			CurrentForegroundWindow = hWndTray;
		}
	}

	if (PrintDebugInfo) {
		std::wcout << L"SameUniqueDragSession True/False: " << SameUniqueDragSession << L" Window:" << CurrentForegroundWindow << endl;
	}

	Previous_UniqueID_of_the_click_Best_Method_Ever = Current_UniqueID_of_the_click;

	bool WithShift = false;
	float Half_of_Buttons = (float)AllButtonsNumber / 2;

	int RealNumberToClick = ButtonID;

	if (!SameUniqueDragSession) {
		//Hotfix, it needs + 1;
		RealNumberToClick = RealNumberToClick + 1;
		if ((float)ButtonID <= Half_of_Buttons) {
			WithShift = false;
		}
		else {
			WithShift = true;
			RealNumberToClick = AllButtonsNumber - ButtonID;
			//Hotfix, it needs + 1;
			RealNumberToClick = RealNumberToClick + 1;
		}
	}
	else {
		RealNumberToClick = abs(Previous_Button_Number - ButtonID);
		if (ButtonID == Previous_Button_Number) {
			//Do nothing
			RealNumberToClick = 0;
			WithShift = false;
		}
		else if (ButtonID > Previous_Button_Number) {
			WithShift = false;
		}
		else if (ButtonID < Previous_Button_Number) {
			WithShift = true;
		}
	}

	PreviousForegroundWindow = CurrentForegroundWindow;

	if (PrintDebugInfo) {
		std::wcout << L"Half_of_Buttons: " << Half_of_Buttons << L". ButtonID:" << ButtonID << L". AllButtonsNumber: " << AllButtonsNumber << L". RealNumberToClick: " << RealNumberToClick << L". WithShift:" << WithShift << endl;
	}

	//Win+SHIFT+T is reverse order.
	bool ArrowsMethod = true;

	if (ArrowsMethod) {
		//We need to use arrows instead
		if (RealNumberToClick > 0) {

			//Hotfix ver. 1.3.1, set focus to hWndTray to fix Task Manager causing hotkey not activating issues.
			SetForegroundWindow(hWndTray);
			SetActiveWindow(hWndTray);
			SetFocus(hWndTray);

			//Unfortunately, WM_HOTKEY is not so perfect. Buggy when switching to window and back to taskbar without dropping.
			/*LRESULT SendMessageReturn;
			if (WithShift) {
				SendMessageReturn = SendMessage(hWndTray, WM_HOTKEY, (WPARAM)0x1FF, (LPARAM)0x0054000C);
			}
			else {
				SendMessageReturn = SendMessage(hWndTray, WM_HOTKEY, (WPARAM)0x1FE, (LPARAM)0x00540008);
			}
			Sleep(50);
			std::wcout << L"RealNumberToClick > 0. SendMessageReturn: " << SendMessageReturn << endl;*/

			//Check if CTRL is pressed, because this hotkey won't activate with it:
			bool CTRL_Was_Down = false;
			if (GetKeyState(REMAP_VK_LCONTROL) & 0x8000)
			{
				CTRL_Was_Down = true;
				keybd_event(REMAP_VK_LCONTROL, VIRTUAL_REMAP_VK_LCONTROL, KEYEVENTF_KEYUP, 0);//Release CTRL
			}

			//For some reasons doesn't seem to work, but we can leave it in code.
			bool ALT_Was_Down = false;
			if (GetKeyState(REMAP_VK_MENU) & 0x8000)
			{
				ALT_Was_Down = true;
				keybd_event(REMAP_VK_MENU, VIRTUAL_REMAP_VK_MENU, KEYEVENTF_KEYUP, 0);//Release ALT
			}

			if (CTRL_Was_Down || ALT_Was_Down) {
				if (HowLongSleepBetweenDifferentKeysPressMilliseconds > 0) {
					Sleep(HowLongSleepBetweenDifferentKeysPressMilliseconds);
				}
			}

			keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, 0, 0);//Pres Logo Win
			if (WithShift) {
				keybd_event(REMAP_VK_LSHIFT, VIRTUAL_REMAP_VK_LSHIFT, 0, 0);//Pres Shift
			}
			keybd_event(REMAP_VK_T, VIRTUAL_REMAP_VK_T, 0, 0);//Press T
			if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
				Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
			}
			keybd_event(REMAP_VK_T, VIRTUAL_REMAP_VK_T, KEYEVENTF_KEYUP, 0); //Release T
			if (WithShift) {
				keybd_event(REMAP_VK_LSHIFT, VIRTUAL_REMAP_VK_LSHIFT, KEYEVENTF_KEYUP, 0);//Release Shift
			}
			keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, KEYEVENTF_KEYUP, 0);//Release Logo Win
			
			if (HowLongSleepBetweenDifferentKeysPressMilliseconds > 0) {
				Sleep(HowLongSleepBetweenDifferentKeysPressMilliseconds);
			}

			//Push CTRL again not to interrupt user's action
			if (CTRL_Was_Down) {
				keybd_event(REMAP_VK_LCONTROL, VIRTUAL_REMAP_VK_LCONTROL, 0, 0);//Pres Ctrl
			}
			if (ALT_Was_Down) {
				keybd_event(REMAP_VK_MENU, VIRTUAL_REMAP_VK_MENU, 0, 0);//Pres Alt
			}

			for (int iii = 0; iii < RealNumberToClick - 1; iii++) {
				if (WithShift) {
					keybd_event(REMAP_VK_LEFT, VIRTUAL_REMAP_VK_LEFT, 0, 0);
					if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
						Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
					}
					keybd_event(REMAP_VK_LEFT, VIRTUAL_REMAP_VK_LEFT, KEYEVENTF_KEYUP, 0);
				}
				else {
					keybd_event(REMAP_VK_RIGHT, VIRTUAL_REMAP_VK_RIGHT, 0, 0);
					//keybd_event(REMAP_VK_RCONTROL, VIRTUAL_REMAP_VK_RCONTROL, 0, 0);
					if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
						Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
					}
					keybd_event(REMAP_VK_RIGHT, VIRTUAL_REMAP_VK_RIGHT, KEYEVENTF_KEYUP, 0);
					//keybd_event(REMAP_VK_RCONTROL, VIRTUAL_REMAP_VK_RCONTROL, KEYEVENTF_KEYUP, 0);
				}
				//std::wcout << L"Click" << iii << endl;
				if (HowLongSleepBetweenTheSameKeysPressMilliseconds) {
					Sleep(HowLongSleepBetweenTheSameKeysPressMilliseconds);
				}
			}

			//ver 1.3.0

			if (AutoOpenFirstWindowInBestMethodEver) {
				if ((JustClickedEnterForBestMethodEver < 2) || (Previous_Button_Number != ButtonID)) {
					Check_And_Issue_Auto_Enter_Best_Method_Ever(ButtonID);
				}

			}
		}

		/*for (int iii = 0; iii < RealNumberToClick; iii++) {
			if (WithShift) {
				LRESULT SendMessageReturn = SendMessage(hWndTray, WM_HOTKEY, (WPARAM)0x1FF, (LPARAM)0x0054000C);
			}
			else {
				LRESULT SendMessageReturn = SendMessage(hWndTray, WM_HOTKEY, (WPARAM)0x1FE, (LPARAM)0x00540008);
			}
			std::wcout << L"Click" << iii << endl;
			Sleep(1);
		}*/

		/*keybd_event(REMAP_VK_UP, VIRTUAL_REMAP_VK_UP, 0, 0); //Press Up
		Sleep(1);
		keybd_event(REMAP_VK_UP, VIRTUAL_REMAP_VK_UP, KEYEVENTF_KEYUP, 0); //Release Up*/

		//HWND FocusedWindow = GetFocus();
		if (PrintDebugInfo) {
			HWND FocusedWindow = GetForegroundWindow();
			wchar_t ActiveWindowBeforeText[MAX_PATH];
			wchar_t ActiveWindowBeforeClassName[MAX_PATH];
			SendMessageW(FocusedWindow, WM_GETTEXT, MAX_PATH, (LPARAM)ActiveWindowBeforeText);
			GetClassNameW(FocusedWindow, ActiveWindowBeforeClassName, MAX_PATH);
			//std::wcout << L"Finally_The_Best_Method_Ever() Focused Window INFO: " << FocusedWindow << endl;
			std::wcout << L"Finally_The_Best_Method_Ever() Foreground Window INFO: " << FocusedWindow << L" " << ActiveWindowBeforeText << L" (" << ActiveWindowBeforeClassName << L")" << endl;
		}
	}
	else {
		for (int iii = 0; iii < RealNumberToClick; iii++) {
			keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, 0, 0);//Pres Logo Win
			Sleep(1);
			if (WithShift) {
				keybd_event(REMAP_VK_LSHIFT, VIRTUAL_REMAP_VK_LSHIFT, 0, 0);//Pres Shift
			}
			Sleep(1);
			keybd_event(REMAP_VK_T, VIRTUAL_REMAP_VK_T, 0, 0);//Press T
			Sleep(1);
			keybd_event(REMAP_VK_T, VIRTUAL_REMAP_VK_T, KEYEVENTF_KEYUP, 0); //Release T
			Sleep(1);
			if (WithShift) {
				keybd_event(REMAP_VK_LSHIFT, VIRTUAL_REMAP_VK_LSHIFT, KEYEVENTF_KEYUP, 0);//Pres Shift
			}
			Sleep(1);
			keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, KEYEVENTF_KEYUP, 0);//Release Logo Win
			Sleep(1);
		}
		/*Sleep(10);
		//Press arrow up to reset selection
		keybd_event(REMAP_VK_UP, VIRTUAL_REMAP_VK_UP, 0, 0); //Press Up
		Sleep(1);
		keybd_event(REMAP_VK_UP, VIRTUAL_REMAP_VK_UP, KEYEVENTF_KEYUP, 0); //Release Up*/
	}
	Previous_Button_Number = ButtonID;
	Previous_WindowsScreenSet = WindowsScreenSet;
}

static BOOL CALLBACK enumChildWindowCallback_SecondaryTrayWnd(HWND hWnd, LPARAM lparam) {
	wchar_t Buffor[MAX_PATH];
	GetClassNameW(hWnd, Buffor, MAX_PATH);
	wstring ClassName = L"UNKNOWN";
	if (wcslen(Buffor) > 1) {
		ClassName = Buffor;
	}
	wstring ClassNameLower = Mona_toLowerWs(ClassName);
	if (ClassNameLower == L"workerw") {
		TmpWorkerW = hWnd;
		EnumChildWindows(hWnd, enumChildWindowCallback_SecondaryTrayWnd, NULL);
	}
	else if (ClassNameLower == L"mstasklistwclass") {
		TmpTaskList = hWnd;
		//EnumChildWindows(hWnd, enumChildWindowCallback_SecondaryTrayWnd, NULL);
	}

	return TRUE;
}

static BOOL CALLBACK enumWindowCallback_SecondaryTrayWnd(HWND hWnd, LPARAM lparam) {
	wchar_t Buffor[MAX_PATH];
	GetClassNameW(hWnd, Buffor, MAX_PATH);

	wstring ClassName = L"UNKNOWN";
	if (wcslen(Buffor) > 1) {
		ClassName = Buffor;
	}
	wstring ClassNameLower = Mona_toLowerWs(ClassName);
	if (ClassNameLower == L"shell_secondarytraywnd") {
		CurrentSecondaryScreen = windowsHWNDs();
		TmpWorkerW = NULL;
		TmpTaskList = NULL;
		CurrentSecondaryScreen.hWndTray = hWnd;
		EnumChildWindows(hWnd, enumChildWindowCallback_SecondaryTrayWnd, NULL);
		CurrentSecondaryScreen.hWndMSTaskSwWClass = TmpTaskList;
		Array_Windows_by_Screen.push_back(CurrentSecondaryScreen);
	}
	return TRUE;
}

bool Fix_Taskbar_Size_Bug(HWND Moomintrollen) {
	RECT SleepModeFix_rect;
	GetWindowRect(Moomintrollen, &SleepModeFix_rect);
	int SleepModeFixTaskbarHeight = SleepModeFix_rect.bottom - SleepModeFix_rect.top;

	if (SleepModeFixTaskbarHeight < 44) { //48 is normal height, 40 when bug occurs, so lets make it 44.
		//Bug occurred
		TaskbarSizeBugDetectedTimes++;
		if (TimeNow.count() > LastTimeFixedTaskbarSizeBug.count() + 5000) {//We can have 5 secs here because it counts real time, not GetTickCount() which would not differ much after the sleep mode.
			
			if (Hwnd && !FixForBugAfterSleepModeUseOldMethod) {
				if (PrintDebugInfo) {
					std::wcout << L"MSTaskSwWClass size bug detected. The current height is: " << SleepModeFixTaskbarHeight << L" (and should be 48). Opening an empty Windows11DragAndDropToTaskbarFix window to fix it...\n";
				}
				if (ShowConsoleWindowOnStartup) {
					ShowWindow(GetConsoleWindow(), SW_HIDE);
				}
				ShowWindow(Hwnd, SW_HIDE);
				Sleep(5);
				ShowWindow(Hwnd, SW_SHOW);
				Sleep(FixForBugAfterSleepModeWindowDisplayTimeMilliseconds);//Attempt to fix issue https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/issues/45
				ShowWindow(Hwnd, SW_HIDE);
				if (ShowConsoleWindowOnStartup) {
					ShowWindow(GetConsoleWindow(), SW_SHOW);
				}
				LastTimeFixedTaskbarSizeBug = TimeNow;//was missing before ver 1.10
			}
			else {
				if (PrintDebugInfo) {
					std::wcout << L"MSTaskSwWClass size bug detected. The current height is: " << SleepModeFixTaskbarHeight << L" (and should be 48). Starting a new CMD window to fix it...\n";
				}
				wstring EmptyWindowCommand = L"start cmd.exe /C \"echo Windows11DragAndDropToTaskbarFix.exe & echo https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix & echo A bug after the Sleep Mode has been detected. The MSTaskSwWClass window size returns incorrect RECT, therefore a new CMD window was open in order to force the taskbar window update. & echo Please read the GitHub page for more details. & timeout 1 & exit\"";
				_wsystem(EmptyWindowCommand.c_str());
				LastTimeFixedTaskbarSizeBug = TimeNow;
			}
			return true;
		}
	}
	return false;
}

void Update_Primary_Screen_Windows_HWNDSs() {
	PrimaryScreen = windowsHWNDs();
	PrimaryScreen.hWndTray = FindWindow(L"Shell_TrayWnd", nullptr);
	if (PrimaryScreen.hWndTray) {
		PrimaryScreen.hWndStartBTNClass = FindWindowEx(PrimaryScreen.hWndTray, 0, L"Start", nullptr); // Start Btn hWnd

		PrimaryScreen.hWndTrayNotify = FindWindowEx(PrimaryScreen.hWndTray, 0, L"TrayNotifyWnd", nullptr);
		//std::cout << "PrimaryScreen.hWndTrayNotify: " << PrimaryScreen.hWndTrayNotify << "\n";
		PrimaryScreen.hWndRebar = FindWindowEx(PrimaryScreen.hWndTray, 0, L"ReBarWindow32", nullptr);
		PrimaryScreen.DesktopWindowXamlSourceHwnd = FindWindowEx(PrimaryScreen.hWndTray, 0, L"Windows.UI.Composition.DesktopWindowContentBridge", nullptr);
	}
	if (PrimaryScreen.hWndRebar) {
		PrimaryScreen.hWndMSTaskSwWClass = FindWindowEx(PrimaryScreen.hWndRebar, 0, L"MSTaskSwWClass", nullptr);
		PrimaryScreen.TaskListThumbnailWnd = FindWindowEx(NULL, 0, L"TaskListThumbnailWnd", nullptr);
	}
}


HINSTANCE hInst;

DWORD WINAPI ProgramWindowThread(void* data) {

	/*bool CreateTaskManagerButtonOnTaskbar = false;
	if (CreateTaskManagerButtonOnTaskbar) {
		int popUPWidth = 151;
		int popUPHeight = 37;

		HRGN Rounded = CreateRoundRectRgn(0, 0, popUPWidth, popUPHeight, 20, 20);

		//Task manager button window:

		// The main window class name.
		bool CreatedTaskManagerButton = false;
		static wchar_t szWindowClass[] = L"Windows11DragAndDropToTaskbarFixTaskManager";
		// The string that appears in the application's title bar.
		static wchar_t szTitle[] = L"Windows 11 Drag & Drop to the Taskbar(Fix)";

		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstWindow;
		wcex.hIcon = LoadIcon(hInstWindow, MAKEINTRESOURCE(IDI_APPLICATION));
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(48, 51, 56)));
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

		if (!RegisterClassEx(&wcex))
		{
				//return 1;
		}
		else {
			CreatedTaskManagerButton = true;
		}

		if (CreatedTaskManagerButton) {
			CreatedTaskManagerButton = false;
			hInst = hInstWindow; // Store instance handle in our global variable

			HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW,
				szWindowClass,
				szTitle,
				WS_POPUP,
				CW_USEDEFAULT, CW_USEDEFAULT,
				popUPWidth, popUPHeight,
				NULL,
				NULL,
				hInstWindow,
				NULL
			);

			if (!hWnd)
			{
	
			}
			else {
				CreatedTaskManagerButton = true;
			}
			// The parameters to ShowWindow explained:
			// hWnd: the value returned from CreateWindow
			// nCmdShow: the fourth parameter from WinMain
			if (CreatedTaskManagerButton) {
				SetWindowRgn(hWnd, Rounded, TRUE);
				ShowWindow(hWnd,
					SW_SHOW);
				UpdateWindow(hWnd);
			}
		}
	}*/

	

	MSG messages;
	WNDCLASSEXW wincl;
	WM_TASKBAR = RegisterWindowMessageW(L"Windows11DragAndDropToTaskbarFixTaskbarCreated");

	wincl.hInstance = hInstWindow;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof(WNDCLASSEX);
	if (!UseAlternativeTrayIcon) {
		wincl.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		wincl.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	}
	else {
		wincl.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
		wincl.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
	}
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	wincl.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 255, 255)));
	/* Register the window class, and if it fails quit the thread */
	if (!RegisterClassEx(&wincl))
		return 0;

	/* The class is registered, let's create the program*/
	Hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		szTitleName,       /* Title Text */
		//WS_OVERLAPPEDWINDOW, /* default window */
		WS_OVERLAPPED | WS_SYSMENU, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		//544,                 /* The programs width */
		10,                 /* The programs width */
		//375,                 /* and height in pixels */
		10,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hInstWindow,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);
	/*Initialize the NOTIFYICONDATA structure only once*/
	if (ShowTrayIcon) {
		InitNotifyIconData();
	}

	//ShowWindow(Hwnd, nShowCmdWindow);

	//Hide window on program startup.
	ShowWindow(Hwnd, SW_HIDE);
	if (ShowTrayIcon) {
		Shell_NotifyIcon(NIM_ADD, &notifyIconData);
	}

	while (GetMessage(&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}

	return (DWORD)messages.wParam;
}


bool IsCursorIconAllowed() {
	CURSORINFO cursorInfo = { 0 };
	cursorInfo.cbSize = sizeof(cursorInfo);
	if (::GetCursorInfo(&cursorInfo))
	{
		if (PrintDebugInfo) {
			std::wcout << L"Cursor Info: " << cursorInfo.hCursor << endl;
		}
		HCURSOR hCursorBeam = LoadCursor(NULL, IDC_IBEAM);
		if (cursorInfo.hCursor == hCursorBeam) {
			return false;
		}
		//Excel + icon:
		/*if (cursorInfo.hCursor == (HCURSOR)0xB09CB) {
			return false;
		}*/
	}
	return true;
}

bool IsCurrentCursorIconStopOrDrag() {
	CURSORINFO cursorInfo = { 0 };
	cursorInfo.cbSize = sizeof(cursorInfo);
	if (::GetCursorInfo(&cursorInfo))
	{
		if (PrintDebugInfo) {
			std::wcout << L"IsCurrentCursorIconStop(): Cursor Info: " << cursorInfo.hCursor << endl;
		}

		/*HCURSOR hCursorBeam = LoadCursor(NULL, IDC_NO);
		if (cursorInfo.hCursor == hCursorBeam) {
			return true;
		}*/

		if (cursorInfo.hCursor == (HCURSOR)0x170DE9 || cursorInfo.hCursor == (HCURSOR)0x10017) {
			return true;
		}
	}
	return false;
}

void AdvancedSleep() {
	if (UseFixForBugAfterSleepMode) {
		SleepModeFix_Previous_TimeNow = TimeNow;
	}
	Sleep(SleepPeriodNow);
}

void Update_Pseudo_DPI_Scale() {
	double UpdatedDPIScaleX = 1.0;
	double UpdatedDPIScaleY = 1.0;
	//https://stackoverflow.com/questions/33507031/detect-if-non-dpi-aware-application-has-been-scaled-virtualized/36864741
	//Get current monitor:
	HMONITOR hMonitor = MonitorFromPoint(P, MONITOR_DEFAULTTONEAREST);

	// Get the logical width and height of the monitor.
	MONITORINFOEX miex;
	miex.cbSize = sizeof(miex);
	GetMonitorInfo(hMonitor, &miex);
	int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
	int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);
	if (PrintDebugInfo) {
		std::wcout << L"Update_Pseudo_DPI_Scale = cxLogical: " << cxLogical << ". cyLogical: " << cyLogical << "." << endl;
	}

	// Get the physical width and height of the monitor.
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;
	int cyPhysical = dm.dmPelsHeight;
	if (PrintDebugInfo) {
		std::wcout << L"Update_Pseudo_DPI_Scale = cxPhysical: " << cxPhysical << ". cyPhysical: " << cyPhysical << "." << endl;
	}

	// Calculate the scaling factor.
	double horzScale = ((double)cxPhysical / (double)cxLogical);
	double vertScale = ((double)cyPhysical / (double)cyLogical);
	if (PrintDebugInfo) {
		std::wcout << L"Update_Pseudo_DPI_Scale = horzScale: " << horzScale << ". vertScale: " << vertScale << "." << endl;
	}
	//it differs sometimes:
	/*if (horzScale == vertScale) {
		UpdatedDPIScale = vertScale;
	}*/
	if (horzScale >= 1.0f && horzScale < 10.1f) {
		UpdatedDPIScaleX = horzScale;
	}
	else {
		if (PrintDebugInfo) {
			std::wcout << L"Update_Pseudo_DPI_Scale !!! Incorrect horzScale detected !!!." << endl;
		}
	}

	if (vertScale >= 1.0f && vertScale < 10.1f) {
		UpdatedDPIScaleY = vertScale;
	}
	else {
		if (PrintDebugInfo) {
			std::wcout << L"Update_Pseudo_DPI_Scale !!! Incorrect vertScale detected !!!." << endl;
		}
	}

	Current_DPI_Scale_X = UpdatedDPIScaleX;
	Current_DPI_Scale_Y = UpdatedDPIScaleY;
}

int CheckControlPixelsAboveTheMouseOnTaskbar() {
	//Update DPI only if different session ID, or if mouse enters a different monitor.
	if ((Current_UniqueID_of_the_click != Previous_DPI_UniqueID_of_the_click) || (WindowsScreenSet != PreviousDPI_WindowsScreenSet)) {
		Update_Pseudo_DPI_Scale();
		Previous_DPI_UniqueID_of_the_click = Current_UniqueID_of_the_click;
		PreviousDPI_WindowsScreenSet = WindowsScreenSet;
		if (PrintDebugInfo) {
			std::wcout << L"Different Session ID or Monitor detected. Current DPI X: " << Current_DPI_Scale_X << ". Y: " << Current_DPI_Scale_Y << "." << endl;
		}
	}

	//we have cursor position P updated in the code earlier, so no need to do this again.

	//15 = 242 242 242 #F2F2F2
	//21 = 255 0 0 #FF0000

	int ToReturn = 0;
	COLORREF PrevColor1 = RGB(0, 0, 0);
	COLORREF PrevColor2 = RGB(0, 0, 0);
	COLORREF PrevColor3 = RGB(0, 0, 0);

	COLORREF our_white = RGB(242, 242, 242);
	COLORREF our_red = RGB(255, 0, 0);

	HDC dc = GetDC(NULL);
	int PointYScaled = static_cast<int>((P.y * Current_DPI_Scale_Y));
	int PointXScaled = static_cast<int>((P.x * Current_DPI_Scale_X));

	int PointYScaledTmp = PointYScaled;
	//std::wcout << L"TEST. Current DPI X: " << Current_DPI_Scale_X << ". Y: " << Current_DPI_Scale_Y << "." << endl;
	
	//OMG, we need to loop 3 times because of Windows Updates changing this incorrect sign instead of fixing it. Disgusting:
	bool FoundColor = false;
	for (int mona = 0; mona < 3; mona++){
		if (FoundColor) {
			break;
		}
		PrevColor1 = RGB(0, 0, 0);
		PrevColor2 = RGB(0, 0, 0);
		PrevColor3 = RGB(0, 0, 0);
		if (mona == 0) {
			//Some old Win11 version
			our_white = RGB(242, 242, 242);
			our_red = RGB(255, 0, 0);
		}
		else if (mona == 1) {
			//White 23H2 theme:
			our_white = RGB(252, 252, 252);
			our_red = RGB(51, 51, 51);
		}
		else if (mona == 2) {
			//Dark 23H2 theme:
			our_white = RGB(44, 44, 44);
			our_red = RGB(232, 232, 232);
		}

		for (int iii = 14; iii < 31; iii++) {
			int PointYWithOffsetNow = PointYScaledTmp - iii;
			COLORREF color_now = GetPixel(dc, PointXScaled, PointYWithOffsetNow);
			//std::wcout << L"Color ID " << iii << L"= R: " << GetRValue(color_now) << L" G: " << GetGValue(color_now) << L" B: " << GetBValue(color_now) << endl;
			if (color_now == our_red) {
				if (PrevColor1 == our_white && PrevColor2 == our_white && PrevColor3 == our_white) {
					ToReturn = 1;
					FoundColor = true;
					break;
				}
			}
			PrevColor1 = PrevColor2;
			PrevColor2 = PrevColor3;
			PrevColor3 = color_now;
		}
	}
	ReleaseDC(NULL, dc);

	//Hotfix. To make life easier, we will always return true when the drag and drop was clicked on a different monitor than the current one. It should fix repoted problems,
	//and shouldn't cause any extra problems like with documents scrolling, because they're usually done on the same screen.
	if (ToReturn == 0) {
		//Get current monitor:
		HMONITOR hMonitorClickStart = MonitorFromPoint(MouseClickStartPoint, MONITOR_DEFAULTTONEAREST);
		HMONITOR hMonitorNow = MonitorFromPoint(P, MONITOR_DEFAULTTONEAREST);
		if (hMonitorClickStart != hMonitorNow) {
			ToReturn = 2;
			if (PrintDebugInfo) {
				std::wcout << L"CheckControlPixelsAboveTheMouseOnTaskbar() was about to return 0, but the program detected that the mouse was clicked on a different monitor than the destination monitor, so we will return 2 to minimize the risk of reported issues." << endl;
			}
		}
	}

	return ToReturn;

	/*int PointYWithOffset1 = static_cast<int>((P.y * Current_DPI_Scale_Y)) - 15;
	COLORREF color1 = GetPixel(dc, static_cast<int>((P.x * Current_DPI_Scale_X)), PointYWithOffset1);
	if (color1 == RGB(242, 242, 242)) {
		int PointYWithOffset2 = static_cast<int>((P.y * Current_DPI_Scale_Y)) - 21;
		COLORREF color2 = GetPixel(dc, static_cast<int>((P.x * Current_DPI_Scale_X)), PointYWithOffset2);
		if (color2 == RGB(255, 0, 0)) {
			ToReturn = true;
		}
	}
	ReleaseDC(NULL, dc);
	return ToReturn;*/

	/*PrintDebugInfo = false;
	HDC dcTest = GetDC(NULL);
	for (int iii = 0; iii < 40; iii++) {
		int PointYWithOffset = static_cast<int>((P.y * Current_DPI_Scale_Y)) - iii;
		COLORREF color_current = GetPixel(dcTest, static_cast<int>((P.x * Current_DPI_Scale_X)), PointYWithOffset);
		printf("Mouse X: %i, Y: %i. Offset: %i (%i). R: %i, G: %i, B: %i\n", P.x, P.y, iii, PointYWithOffset, GetRValue(color_current), GetGValue(color_current), GetBValue(color_current));
	}
	ReleaseDC(NULL, dcTest);
	return false;*/
}


bool KnownPixelColors_CookieFileExists() {
	//Windows11DragAndDropToTaskbarPartialFix
	wstring TmpFile = std::filesystem::temp_directory_path().wstring() + KnownPixelDetectedCookieFilename;
	if (FileExists(TmpFile.c_str())) {
		return true;
	}
	return false;
}

bool KnownPixelColors_CookieFileCreate() {
	wstring TmpFile = std::filesystem::temp_directory_path().wstring() + KnownPixelDetectedCookieFilename;
	HANDLE h = CreateFileW(TmpFile.c_str(),    // name of the file
		GENERIC_WRITE, // open for writing
		0,             // sharing mode, none in this case
		0,             // use default security descriptor
		CREATE_ALWAYS, // overwrite if exists
		FILE_ATTRIBUTE_NORMAL,
		0);
	if (h)
	{
		CloseHandle(h);
		return true;
		//std::cout << "CreateFile() succeeded\n";
	}
	else
	{
		//std::cerr << "CreateFile() failed:" << GetLastError() << "\n";
	}
	return false;
}

BOOL IsElevated() {
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	return fRet;
}

int Return_Current_Taskbar_Window_Width() {
	if (PrimaryScreen.hWndMSTaskSwWClass) {
		RECT rect;
		GetWindowRect(PrimaryScreen.hWndMSTaskSwWClass, &rect);
		int Difference = rect.right - rect.left;
		return Difference;
	}
	return 6969;
}


//Unused!
void Auto_Detect_And_Fix_Incorrect_MSTaskSwWClass_WindowSize() {
	if (AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize) {
		std::wcout << L"AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize is ENABLED. Trying to auto-detect the offset..." << endl;
		if (ShowConsoleWindowOnStartup) {
			ShowWindow(GetConsoleWindow(), SW_HIDE);
		}
		Sleep(HowLongSleepWhenAutoDetectingMSTaskSwWClassWindowMilliseconds);
		Update_Primary_Screen_Windows_HWNDSs();
		bool DetectedCorrectly = false;
		int InitialWidth = Return_Current_Taskbar_Window_Width();
		if (InitialWidth != 6969) {
			ShowWindow(GetConsoleWindow(), SW_SHOW);
			Sleep(HowLongSleepWhenAutoDetectingMSTaskSwWClassWindowMilliseconds);
			Update_Primary_Screen_Windows_HWNDSs();
			int SecondWidth = Return_Current_Taskbar_Window_Width();
			if (SecondWidth != 6969) {
				int InitialSecondDifference = SecondWidth - InitialWidth;
				std::wcout << L"AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize: InitialWidth: " << InitialWidth << L". SecondWidth: " << SecondWidth << L". Difference: " << InitialSecondDifference << L"." << endl;

				if (InitialSecondDifference >= 0) {
					ShowWindow(GetConsoleWindow(), SW_HIDE);
					Sleep(HowLongSleepWhenAutoDetectingMSTaskSwWClassWindowMilliseconds);
					Update_Primary_Screen_Windows_HWNDSs();
					int ThirdWidth = Return_Current_Taskbar_Window_Width();
					if (ThirdWidth != 6969) {
						int ThirdWidthDiff = ThirdWidth - SecondWidth;
						int ThirdAbsoluteDiff = abs(ThirdWidthDiff);
						std::wcout << L"AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize: ThirdWidth: " << ThirdWidth << L". ThirdWidth and SecondWidth ABS difference: " << ThirdAbsoluteDiff << L"." << endl;
						if (ThirdAbsoluteDiff == InitialSecondDifference) {
							//FOUND New Offset!
							DetectedCorrectly = true;
							AutoDetectedSingleIconWidthChangeOffsetSucceed = true;
							AutoDetectedSingleIconWidthChangeOffsetOnMSTaskSwWClassWindow = ThirdAbsoluteDiff;
							std::wcout << L"AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize: Sussessfully detected the single icon offset: " << ThirdAbsoluteDiff << L"." << endl;
						}
					}
				}
			}
		}

		if (!DetectedCorrectly) {
			std::wcout << L"AutoDetectAndFixIncorrectMSTaskSwWClassWindowSize: Auto-detecting offset failed!" << endl;
		}

		if (ShowConsoleWindowOnStartup) {
			ShowWindow(GetConsoleWindow(), SW_SHOW);
		}
	}
}

CComPtr<IUIAutomation> pAutomation;
CComPtr<IUIAutomationElement> pTaskbarElement;
CComPtr<IUIAutomationCondition> pTaskListCondition;

struct IconPosition {
	int x;
	int y;
	int width;
	int height;
	int singleIconWidth;
	int singleIconHeight;
	bool singleIconSizeSet;

	void Reset() {
		x = INT_MAX;
		y = 0;
		width = 0;
		height = 0;
		singleIconWidth = 0;
		singleIconHeight = 0;
		singleIconSizeSet = false;
	}
};

struct TaskbarIconInfo {
	int numberOfIcons;
	int totalWidth;
	IconPosition leftMostIcon;
	IconPosition rightMostIcon;
	int singleIconWidth;
	int singleIconHeight;
	int firstIconX;
	int lastIconXPlusWidth;

	TaskbarIconInfo()
		: numberOfIcons(-1), totalWidth(0), singleIconWidth(0), singleIconHeight(0),
		firstIconX(INT_MAX), lastIconXPlusWidth(-1) {
		leftMostIcon.x = INT_MAX;
		rightMostIcon.x = -1;
	}
};


bool InitializeTaskbarSearch(bool forceReinitialize = false)
{
	if (forceReinitialize)
	{
		pAutomation = nullptr;
		pTaskbarElement = nullptr;
		pTaskListCondition = nullptr;
	}
	if (pTaskbarElement && pTaskListCondition)
		return true;

	if (!pAutomation)
	{
		HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**)&pAutomation);
		if (FAILED(hr)) return false;
	}

	CComPtr<IUIAutomationElement> pRootElement;
	HRESULT hr = pAutomation->GetRootElement(&pRootElement);
	if (FAILED(hr)) return false;

	CComPtr<IUIAutomationCondition> pTaskbarCondition;
	hr = pAutomation->CreatePropertyCondition(UIA_ClassNamePropertyId, CComVariant(L"Shell_TrayWnd"), &pTaskbarCondition);
	if (FAILED(hr)) return false;

	hr = pRootElement->FindFirst(TreeScope_Children, pTaskbarCondition, &pTaskbarElement);
	if (FAILED(hr) || !pTaskbarElement) return false;

	hr = pAutomation->CreatePropertyCondition(UIA_ClassNamePropertyId, CComVariant(L"Taskbar.TaskListButtonAutomationPeer"), &pTaskListCondition);
	if (FAILED(hr)) return false;
	return true;
}

IconPosition GetIconPosition(CComPtr<IUIAutomationElement>& pIcon) {
	IconPosition position = IconPosition();

	CComPtr<IUIAutomationElement> pCurrent = pIcon;
	while (pCurrent) {
		RECT rect;
		if (SUCCEEDED(pCurrent->get_CurrentBoundingRectangle(&rect))) {
			position.x = rect.left;
			position.y = rect.top;
			position.width = rect.right - rect.left;
			position.height = rect.bottom - rect.top;
			break;
		}
		CComPtr<IUIAutomationTreeWalker> pControlViewWalker;
		if (SUCCEEDED(pAutomation->get_ControlViewWalker(&pControlViewWalker))) {
			CComPtr<IUIAutomationElement> pParent;
			if (SUCCEEDED(pControlViewWalker->GetParentElement(pCurrent, &pParent)) && pParent) {
				pCurrent = pParent;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}

	return position;
}

void UpdateGlobalIconPositions(IconPosition& iconPos, TaskbarIconInfo& result) {

	if (iconPos.x <= result.firstIconX) {
		result.firstIconX = iconPos.x;
	}
	if ((iconPos.x + iconPos.width) >= result.lastIconXPlusWidth) {
		result.lastIconXPlusWidth = iconPos.x + iconPos.width;
	}

	if (iconPos.x <= result.leftMostIcon.x) {
		result.leftMostIcon = iconPos;
		result.singleIconWidth = iconPos.width;
		result.singleIconHeight = iconPos.height;
		result.totalWidth = result.lastIconXPlusWidth - result.firstIconX;
	}
	if (iconPos.x >= result.rightMostIcon.x) {
		result.rightMostIcon = iconPos;
		result.singleIconWidth = iconPos.width;
		result.singleIconHeight = iconPos.height;
		result.totalWidth = result.lastIconXPlusWidth - result.firstIconX;
	}
}

TaskbarIconInfo GetNumberOfIconsAndCalculateWidth() {
	TaskbarIconInfo result = TaskbarIconInfo();
	if (!InitializeTaskbarSearch()) {
		if (PrintDebugInfo) {
			std::cerr << "Failed to initialize taskbar search" << std::endl;
		}
		return result;
	}

	/*RECT taskbarRect = {};
	HRESULT hr = pTaskbarElement->get_CurrentBoundingRectangle(&taskbarRect);
	if (FAILED(hr)) {
		std::cerr << "Failed to get taskbar's bounding rectangle" << std::endl;
		return result;
	}*/

	CComPtr<IUIAutomationElementArray> pTaskbarButtonElements;
	HRESULT hr = pTaskbarElement->FindAll(TreeScope_Descendants, pTaskListCondition, &pTaskbarButtonElements);
	if (FAILED(hr)) {
		if (PrintDebugInfo) {
			std::cerr << "Failed to find taskbar button elements" << std::endl;
		}
		return result;
	}

	int count = 0;
	hr = pTaskbarButtonElements->get_Length(&count);
	if (FAILED(hr)) {
		if (PrintDebugInfo) {
			std::cerr << "Failed to get count of taskbar button elements" << std::endl;
		}
		return result;
	}

	result.numberOfIcons = count;

	for (int i = 0; i < count; ++i) {
		CComPtr<IUIAutomationElement> pIcon;
		hr = pTaskbarButtonElements->GetElement(i, &pIcon);
		if (SUCCEEDED(hr) && pIcon) {
			IconPosition iconPos = GetIconPosition(pIcon);
			UpdateGlobalIconPositions(iconPos, result);
		}
	}
	if (PrintDebugInfo) {
		std::cout << "Taskbar icons width: " << result.totalWidth << std::endl;
	}
	return result;
}


int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPWSTR lpCmdLine, int nShowCmd)
{
	hPrevWindow = hPrev;
	hInstWindow = hInst;
	nShowCmdWindow = nShowCmd;
	CurrentProcessID = GetCurrentProcessId();
	//Important to make reading .lnk possible:
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

	bool IgnoreMutex = false;
	wstring Commandline = lpCmdLine;
	if (Commandline.find(L"restart-ignore-mutex") != std::wstring::npos) {
		IgnoreMutex = true;
		size_t RestartedTimesFind = Commandline.find(L"-restarted-times-");
		if(RestartedTimesFind != std::wstring::npos) {
			wstring restartedtimes = Commandline.substr(RestartedTimesFind + 17);
			RestartedTimesFind = restartedtimes.find(L"-");
			if (RestartedTimesFind != std::wstring::npos) {
				RestartedCrashedTimes = _wtoll(restartedtimes.c_str());
			}
		}
	}

	//Load configuration:
	NowSettingsChangeTime = ReturnConfigFileTime();
	LastSettingsChangeTime = NowSettingsChangeTime;
	Mona_Load_Configuration();

	//Custom log file?
	std::wofstream LOG;
	if (HaveCustomLogFile) {
		if (!LOG.is_open())
		{
			if (PrintDebugInfo) {
				wcout << L"Opening the Custom Log File: " << s2ws(CustomLogFile).c_str() << endl;
			}
			LOG.open(CustomLogFile.c_str(), std::ios::trunc);
		}
		if (!LOG.is_open()) {
			if (PrintDebugInfo) {
				wcout << L"Failed to open the log file: " << s2ws(CustomLogFile).c_str() << endl;
			}
		}
		else {
			wcout.rdbuf(LOG.rdbuf());
		}
	}

	//ver 2.2 check if run as administrator:
	if (StartThisProgramAsAdministrator) {
		if (!IsElevated()) {
			if (Commandline.find(L"restart-as-administrator") != std::wstring::npos) {
				//Do nothing, just in case it failed so we don't create a forkbomb
			}
			else {
				wstring RestartNowWstr = L"restart-as-administrator-restart-ignore-mutex";
				ShellExecuteW(NULL, L"runas", CurrentExeWorks.c_str(), RestartNowWstr.c_str(), NULL, SW_SHOW);
				return 0;
			}
		}
	}

	if (IsElevated()) {
		TheProgramIsRunningAsAdministratorRightNow = true;
	}

	bool ReloadConfigToShowDebugInfo = false;
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

		if (!PrintDebugInfo) {
			HMENU hmenu = GetSystemMenu(GetConsoleWindow(), FALSE);
			EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);

			HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
			if (!hInput) {
				hInput = GetConsoleWindow();
			}
			DWORD prev_mode;
			GetConsoleMode(hInput, &prev_mode);
			SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS |
				(prev_mode & ~ENABLE_QUICK_EDIT_MODE));
		}
		else {
			ReloadConfigToShowDebugInfo = true;
		}
	}

	HANDLE handleMutex;
	if (!IgnoreMutex) {
		handleMutex = CreateMutex(NULL, TRUE, L"MonaWindows11DragToTaskbar-AlreadyRunning");
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			wcout << L"Windows11DragAndDropToTaskbarFix is already running. Exiting this instance..." << std::endl;
			return 1;
		}
	}

	//Welcome!
	bool HideConsoleWindowSoon = false;
	std::chrono::milliseconds ProgrmStartTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	wcout << L"Windows11DragAndDropToTaskbarFix, ver. " << ProgramVersion.c_str() << L", created by Dr.MonaLisa." << endl;
	wcout << L"https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix" << endl << endl;
	wcout << L"You can disable the console window. Please read the GitHub page to learn how to configure this program." << endl;
	if (!PrintDebugInfo) {
		wcout << L"Debug output is disabled, so the console window will be hidden in 10 seconds." << endl << L"In order to terminate this program, please kill \"Windows11DragAndDropToTaskbarFix.exe\" in the Task Manager." << endl;
		if (ShowConsoleWindowOnStartup) {
			HideConsoleWindowSoon = true;
		}
	}

	if (ReloadConfigToShowDebugInfo) {
		//Load config AGAIN to show debug output this time.
		Mona_Load_Configuration(true);
	}

	//Ver. 2.4.0 fixes: UNUSED
	//Auto_Detect_And_Fix_Incorrect_MSTaskSwWClass_WindowSize();

	//Check auto start:
	Check_And_Set_Auto_Program_Startup();

	//Start program window thread:
	HANDLE ThreadProgramWindowThread = CreateThread(NULL, 0, ProgramWindowThread, NULL, 0, NULL);

	//Start Mouse Click Watchdog Thread 
	HANDLE ThreadHandleMouseClickWatchdogThread = nullptr;
	if (UseLowLevelMousePressProcThread) {
		ThreadHandleMouseClickWatchdogThread = CreateThread(NULL, 0, MouseClickWatchdogThread, NULL, 0, NULL);
	}

	//Test:
	//TestTryToRestoreWindowsUsingWMCommand();
	//system("pause");
	//exit(0);

	//Get primary Taskbar Height in order to disable UseFixForBugAfterSleepMode if UndockingDisabled:
	if (UseFixForBugAfterSleepMode) {
		Update_Primary_Screen_Windows_HWNDSs();
		if (PrimaryScreen.hWndMSTaskSwWClass) {
			RECT XSleepModeFix_rect;
			GetWindowRect(PrimaryScreen.hWndMSTaskSwWClass, &XSleepModeFix_rect);
			int XSleepModeFixTaskbarHeight = XSleepModeFix_rect.bottom - XSleepModeFix_rect.top;
			if (XSleepModeFixTaskbarHeight < 44) {
				UseFixForBugAfterSleepMode = false;
				//UndockingDisabled
				if (PrintDebugInfo) {
					std::wcout << L"Incorrect taskbar height on program start detected: " << XSleepModeFixTaskbarHeight << L". Possibly `UndockingDisabled` is configured in registry. Setting UseFixForBugAfterSleepMode to FALSE in order to prevent the continuous fix execution." << endl;
				}
			}
		}
	}

	if (DetectKnownPixelColorsToPreventAccidentalEvents) {
		if (KnownPixelColors_CookieFileExists()) {
			CorrectPixelsEverDetectedUsingCookieFile = true;
		}
	}


	while (!InterruptMainThread) {
		try {
			TimeNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

			if (HideConsoleWindowSoon) {
				if (TimeNow.count() >= (ProgrmStartTime.count() + 10000)) {
					HideConsoleWindowSoon = false;
					ShowWindow(GetConsoleWindow(), SW_HIDE);
				}
			}
			//Ver 1.5.1:

			if (UseFixForBugAfterSleepMode) {
				if (SleepModeFix_Previous_TimeNow.count() != 0) {
					long long int TimeToCheck = (DefaultSleepPeriodInTheLoopMilliseconds * 10) + SleepModeFix_Previous_TimeNow.count();
					//std::wcout << L"BUG CHECK. TimeToChecl: " << TimeToCheck << L". TimeNow:" << TimeNow.count() << L"\n";
					if (TimeNow.count() > TimeToCheck) {
						if (PrintDebugInfo) {
							std::wcout << L"Possible wakeup after the Sleep Mode. Checking if the taskbar bug occurred...\n";
						}
						//Possible sleep mode:
						//Copy-paste code because I'm too lazy.
						Update_Primary_Screen_Windows_HWNDSs();

						//Task view rect:
						if (PrimaryScreen.hWndMSTaskSwWClass) {
							Fix_Taskbar_Size_Bug(PrimaryScreen.hWndMSTaskSwWClass);
						}
					}
				}
			}

			//Check for config file update:
			if (ConfigFileChangeTimeMonitorAllowed && (TimeNow.count() > LastTimeCheckedForConfigUpdate.count() + 5000)) {
				LastTimeCheckedForConfigUpdate = TimeNow;
				//We don't need to check if file exists here, as it's done in the function below anyway.
				NowSettingsChangeTime = ReturnConfigFileTime();
				if (NowSettingsChangeTime != 0) {
					if (NowSettingsChangeTime > LastSettingsChangeTime) {
						if (CheckedConfigTimeAtLeastOneTime) {
							//File changed, restart the program?
							wstring ReloadChangesTitie = L"Windows11DragAndDropToTaskbarFix.exe by Dr.MonaLisa:";
							wstring ReloadChangesQuestion = L"The configuration file \"" + ConfigFile + L"\" has been modified by another program.\n\nDo you want to restart \"Windows 11 Drag & Drop to the Taskbar (Fix)\" in order to reload settings?\n\n- Click \"YES\" to reload settings from the file\n\n- Click \"NO\" to keep the current settings\n\n- Click \"CANCEL\" to keep the current settings and to not display this warning again";

							int ReloadChangesConfUtx = IDNO;
							if (!ConfigFileChangeTimeMonitorAutoRestart){
								ReloadChangesConfUtx = MessageBoxW(NULL, ReloadChangesQuestion.c_str(), ReloadChangesTitie.c_str(), MB_YESNOCANCEL | MB_ICONEXCLAMATION | MB_TOPMOST | MB_SETFOREGROUND | MB_DEFBUTTON1);
							}
							else {
								ReloadChangesConfUtx = IDYES;
							}
							if (ReloadChangesConfUtx == IDYES) {
								//NewFunctionToKill(true);
								if (Hwnd) {
									if (ShowTrayIcon) {
										Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
									}
									SendMessage(Hwnd, WM_NULL, 0, 0);
									SendMessage(Hwnd, WM_DESTROY, 0, 0);
								}
								InterruptMouseWatchdogThread = true;
								//NewFunctionToKill(true);
								InterruptRestartProgram = true;
								InterruptMainThread = true;

								break;

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

				CheckedConfigTimeAtLeastOneTime = true;
			}

			//ver 2.4:
			if (!UseLowLevelMousePressProcThread) {
				//LeftButtonPressedATM_Real
				if (!LeftAndRightMouseButtonsAreCurrentlySwapped) {
					if (GetAsyncKeyState(VK_RBUTTON)) {
						if (!RightButtonPressedATM_Real) {
							LastTimeClickedRightMouseButton_Real = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
							GetCursorPos(&MouseClickStartPoint);
							if (!LLMP_Temporarily_Dont_Update_UniqueID) {
								Current_UniqueID_of_the_click++;
							}
						}

						RightButtonPressedATM_Real = true;
						
					}
					else {
						RightButtonPressedATM_Real = false;
					}
				}
				else {
					if (GetAsyncKeyState(VK_LBUTTON)) {
						if (!RightButtonPressedATM_Real) {
							LastTimeClickedRightMouseButton_Real = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
							GetCursorPos(&MouseClickStartPoint);
							if (!LLMP_Temporarily_Dont_Update_UniqueID) {
								Current_UniqueID_of_the_click++;
							}
						}

						RightButtonPressedATM_Real = true;
					}
					else {
						RightButtonPressedATM_Real = false;
					}
				}

				if (!LeftAndRightMouseButtonsAreCurrentlySwapped) {
					if (GetAsyncKeyState(VK_LBUTTON)) {
						if (!LeftButtonPressedATM_Real) {
							LastTimeClickedLeftMouseButton_Real = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
							GetCursorPos(&MouseClickStartPoint);
							if (!LLMP_Temporarily_Dont_Update_UniqueID) {
								Current_UniqueID_of_the_click++;
							}
						}
						LeftButtonPressedATM_Real = true;
						
					}
					else {
						LeftButtonPressedATM_Real = false;
					}
				}
				else {
					if (GetAsyncKeyState(VK_RBUTTON)) {
						if (!LeftButtonPressedATM_Real) {
							LastTimeClickedLeftMouseButton_Real = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
							GetCursorPos(&MouseClickStartPoint);
							if (!LLMP_Temporarily_Dont_Update_UniqueID) {
								Current_UniqueID_of_the_click++;
							}
						}
						LeftButtonPressedATM_Real = true;
						
					}
					else {
						LeftButtonPressedATM_Real = false;
					}
				}
			}

			//ver 1.6, right mouse button support:
			LeftButtonPressedATM = false;//Default
			//We actually don't need to worry too much as tmp variables will be automatically reset below if click UniqueID missmatches.
			Current_Mouse_Button_Zero_Left_One_Right = -1;
			BugMouseButtonNotReallyClicked = false;
			if (RightButtonPressedATM_Real) {
				if (!LeftButtonPressedATM_Real) {
					Current_Mouse_Button_Zero_Left_One_Right = 1;
					LastTimeClickedLeftMouseButton = LastTimeClickedRightMouseButton_Real;
					if (PrintDebugInfo) {
						Current_Button_Name = Button_Name_Right;
					}
					if (!LeftAndRightMouseButtonsAreCurrentlySwapped) {
						if (!GetAsyncKeyState(VK_RBUTTON)) {
							BugMouseButtonNotReallyClicked = true;
						}
					}
					else {
						if (!GetAsyncKeyState(VK_LBUTTON)) {
							BugMouseButtonNotReallyClicked = true;
						}
					}
				}
				else {
					Current_Mouse_Button_Zero_Left_One_Right = 0;
					LastTimeClickedLeftMouseButton = LastTimeClickedLeftMouseButton_Real;
					if (PrintDebugInfo) {
						Current_Button_Name = Button_Name_Left;
					}
					if (!LeftAndRightMouseButtonsAreCurrentlySwapped) {
						if (!GetAsyncKeyState(VK_LBUTTON)) {
							BugMouseButtonNotReallyClicked = true;
						}
					}
					else {
						if (!GetAsyncKeyState(VK_RBUTTON)) {
							BugMouseButtonNotReallyClicked = true;
						}
					}
				}
				LeftButtonPressedATM = true;
			}
			else if (LeftButtonPressedATM_Real) {
				Current_Mouse_Button_Zero_Left_One_Right = 0;
				LastTimeClickedLeftMouseButton = LastTimeClickedLeftMouseButton_Real;
				LeftButtonPressedATM = true;
				if (PrintDebugInfo) {
					Current_Button_Name = Button_Name_Left;
				}
				if (!LeftAndRightMouseButtonsAreCurrentlySwapped) {
					if (!GetAsyncKeyState(VK_LBUTTON)) {
						BugMouseButtonNotReallyClicked = true;
					}
				}
				else {
					if (!GetAsyncKeyState(VK_RBUTTON)) {
						BugMouseButtonNotReallyClicked = true;
					}
				}
			}

			if (BugMouseButtonNotReallyClicked) {

				//Hotfix for GetAsyncKeyState
				int Current_SM_SWAPBUTTON = GetSystemMetrics(SM_SWAPBUTTON);
				if (Current_SM_SWAPBUTTON == 0) {
					LeftAndRightMouseButtonsAreCurrentlySwapped = false;
				}
				else {
					LeftAndRightMouseButtonsAreCurrentlySwapped = true;
				}
				if (LeftAndRightMouseButtonsAreCurrentlySwapped != LeftAndRightMouseButtonsSwappedPreviousStatus) {
					LeftAndRightMouseButtonsSwappedPreviousStatus = LeftAndRightMouseButtonsAreCurrentlySwapped;
					if (LeftAndRightMouseButtonsAreCurrentlySwapped) {
						if (PrintDebugInfo) {
							std::wcout << L"Detected that the Left and the Right mouse buttons are swapped GetSystemMetrics(SM_SWAPBUTTON). Setting LeftAndRightMouseButtonsAreCurrentlySwapped = true.\n";
						}
					}
					else {
						if (PrintDebugInfo) {
							std::wcout << L"Detected that the Left and the Right mouse buttons are NO LONGER swapped GetSystemMetrics(SM_SWAPBUTTON). Setting LeftAndRightMouseButtonsAreCurrentlySwapped = false.\n";
						}
					}
					AdvancedSleep();
					continue;
				}

				LeftButtonPressedATM = false;
				if (PrintDebugInfo) {
					std::wcout << L"A strange problem has been detected. The Low Level Mouse Hook thread claims that the mouse button is pressed, but GetAsyncKeyState returned false. Interrupting not to cause issues.\n";
				}
			}

			//Check if left mouse button is pressed:
			//if (!GetAsyncKeyState(REMAP_VK_LBUTTON)) {
			//In ver 1.1 we use a new thread
			if (!LeftButtonPressedATM) {
				if (CurrentlyLeftMouseButtonIsPressed) {
					ResetTmpVariables();
					CurrentlyLeftMouseButtonIsPressed = false;
				}
			}
			else {
				if (Last_Step_Reached < 1) {
					Last_Step_Reached = 1;
				}

				if (PrintDebugInfo) {
					std::wcout << Current_Button_Name << L" Mouse Button is pressed (SessionID: " << Current_UniqueID_of_the_click << "). Detecting for how long...\n";
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
							std::wcout << L"Different mouse click unique ID detected: " << Current_UniqueID_of_the_click << L". Resetting...\n";
						}
					}
				}

				SleepPeriodNow = SleepPeriodWhenLeftMouseButtonIsPressedInTheLoopMilliseconds;
				CurrentlyLeftMouseButtonIsPressed = true;

				//1.9.2 detect cursor icon to prevent issues when scrolling in the Word document:
				if (IgnorePotentiallyUnwantedDragsFromCertainCursorIcons) {
					if (!DetectedIconInThisClick) {
						DetectedIconInThisClick = true;
						if (!IsCursorIconAllowed()) {
							AllowedCursorIconInThisClick = false;
							if (PrintDebugInfo) {
								std::wcout << L"Disallowed Mouse Cursor Icon detected on click. Ignoring for this click session ID..." << endl;
							}
							AdvancedSleep();
							continue;
						}
					}
					if (!AllowedCursorIconInThisClick) {
						AdvancedSleep();
						continue;
					}
				}

				if ((FirstTimeClickedLeftMouseButton.count() != 0) && (TimeNow.count() >= (FirstTimeClickedLeftMouseButton.count() + HowLongLeftMouseButtonPressedBeforeContinueMilliseconds))) {
					if (Last_Step_Reached < 2) {
						Last_Step_Reached = 2;
					}

					//Continue:
					if (PrintDebugInfo) {
						std::wcout << Current_Button_Name << L" Mouse Button was pressed for > " << HowLongLeftMouseButtonPressedBeforeContinueMilliseconds << L" milliseconds...\n";
					}

					if (!DetectedHWNDsForThisMouseClick) {
						//Primary screen variables:
						Update_Primary_Screen_Windows_HWNDSs();

						//ver 1.6.1: MOVED BELOW
						/*if (UseFixForBugAfterSleepMode) {
							if (PrimaryScreen.hWndMSTaskSwWClass) {
								if (Fix_Taskbar_Size_Bug(PrimaryScreen.hWndMSTaskSwWClass)) {
									//Fixed. Ignore this loop to get potentially new HWND and RECTs.
									DetectedHWNDsForThisMouseClick = false;//IMPORTANT ver. 1.9.1 to fix program crash after the sleep mode.
									AdvancedSleep();
									continue;
								}
							}
						}*/

						Array_Windows_by_Screen.clear();
						//Before version 1.9.1 this array could be empty after the sleep mode bug fix, causing program crashes.
						Array_Windows_by_Screen.push_back(PrimaryScreen);
						//Shell_SecondaryTrayWnd:
						EnumWindows(enumWindowCallback_SecondaryTrayWnd, NULL);

						hDesktop = GetDesktopWindow();
						GetWindowRect(hDesktop, &desktop);
						ShowDesktopStartPosition = desktop.right - DefaultShowDesktopButtonWidth;

						DetectedHWNDsForThisMouseClick = true;//Moved from top to bottom.
					}

					//Unfortunately we can't optimize it at the moment since cursor might move with dragged file from screen-to-screen.
					GetCursorPos(&P);

					HWND WindowUnderMouse = WindowFromPoint(P);
					if (!WindowUnderMouse) {
						POINT P_Hotfix = P;
						P_Hotfix.y = P_Hotfix.y - 1;
						WindowUnderMouse = WindowFromPoint(P_Hotfix);
					}

					WindowsScreenSet = 0;//Primary
					//Secondary Screen Fix ver 1.5:
					GetClassNameW(WindowUnderMouse, WindowClassName, MAX_PATH);
					//std::wcout << L"Class Name Under Mouse: " << WindowClassName << L"\n";
					if (_wcsicmp(WindowClassName, L"MSTaskListWClass") == 0) {
						if (WindowUnderMouse != PrimaryScreen.hWndMSTaskSwWClass) {
							if (PrintDebugInfo) {
								std::wcout << L"Found Taskbar Window on Secondary Screen. Switching HWNDs to the other monitor mode. " << WindowUnderMouse << "\n";
							}

							if (Array_Windows_by_Screen.size() > 0) {
								for (size_t iha = 0; iha < Array_Windows_by_Screen.size(); iha++) {
									if (Array_Windows_by_Screen[iha].hWndMSTaskSwWClass == WindowUnderMouse) {
										WindowsScreenSet = (int)iha;
										if (PrintDebugInfo) {
											std::wcout << L"Found matching window in Array_Windows_by_Screen. " << WindowUnderMouse << "\n";
										}
										break;
									}
								}
							}
						}
					}

					//1.8:
					size_t countVector = Array_Windows_by_Screen.size();
					if (countVector < (WindowsScreenSet + 1)) {
						WindowsScreenSet = 0;
					}

					//ver 1.5 continued:
					//WARNING: Detected some program crashes at this location. Attempting to code it more securely.

					if (Array_Windows_by_Screen[WindowsScreenSet].hWndTray) {
						hWndTray = Array_Windows_by_Screen[WindowsScreenSet].hWndTray;
					}
					else {
						hWndTray = NULL;
					}

					if (hWndTray) {
						if (Array_Windows_by_Screen[0].hWndTrayNotify) {
							hWndTrayNotify = Array_Windows_by_Screen[0].hWndTrayNotify;
						}
						else {
							hWndTrayNotify = NULL;
						}
						if (Array_Windows_by_Screen[0].hWndStartBTNClass) {
							hWndStartBTNClass = Array_Windows_by_Screen[0].hWndStartBTNClass;
						}
						else {
							hWndStartBTNClass = NULL;
						}
					}
					else {
						hWndTrayNotify = NULL;
					}

					if (hWndTray) {
						if (Array_Windows_by_Screen[0].hWndRebar) {
							hWndRebar = Array_Windows_by_Screen[0].hWndRebar;
						}
						else {
							hWndRebar = NULL;
						}
					}
					else {
						hWndRebar = NULL;
					}

					if (hWndRebar) {
						if (Array_Windows_by_Screen[WindowsScreenSet].hWndMSTaskSwWClass) {
							hWndMSTaskSwWClass = Array_Windows_by_Screen[WindowsScreenSet].hWndMSTaskSwWClass;
						}
						else {
							hWndMSTaskSwWClass = NULL;
						}
					}
					else {
						hWndMSTaskSwWClass = NULL;
					}

					//Find a window that should be invisible when app has no active window!
					if (Array_Windows_by_Screen[0].TaskListThumbnailWnd) {
						TaskListThumbnailWnd = Array_Windows_by_Screen[0].TaskListThumbnailWnd;
					}
					else {
						TaskListThumbnailWnd = NULL;
					}

					if (Array_Windows_by_Screen[0].DesktopWindowXamlSourceHwnd) {
						DesktopWindowXamlSourceHwnd = Array_Windows_by_Screen[0].DesktopWindowXamlSourceHwnd;
					}
					else {
						DesktopWindowXamlSourceHwnd = NULL;
					}

					if (PrintDebugInfo) {
						std::wcout << L"Found Taskbar Window: " << hWndMSTaskSwWClass << "\n";
					}
					RECT rect;
					if (hWndMSTaskSwWClass) {
						GetWindowRect(hWndMSTaskSwWClass, &rect);
					}
					else {
						rect.left = 0;
						rect.right = 0;
						rect.bottom = 0;
						rect.top = 0;
					}

					TaskbarWindowWidth = rect.right - rect.left;
					if (PrintDebugInfo) {
						std::wcout << L"Taskbar Window Width: " << TaskbarWindowWidth << L". Taskbar Window Rect: " << rect.left << ":" << rect.right << L":" << rect.bottom << L":" << rect.top << "\n";
					}

					///TEEEEEEEEEEEEEEEEST
					/*RECT startbtn;
					if (hWndStartBTNClass) {
						GetWindowRect(hWndStartBTNClass, &startbtn);
					}
					else {
						if (PrintDebugInfo) {
							std::wcout << L"ERROR hWndStartBTNClass IS NULL\n";
						}
					}

					RECT hWndTryNtfy;
					GetWindowRect(PrimaryScreen.hWndTrayNotify, &hWndTryNtfy);

					// Get taskbar width From left corner of TrayNotif to right side of StartBtn maybe we need some gap between TrayNotif and running apps icon so items on the taskbar will detect correctly
					TaskbarWindowWidth = hWndTryNtfy.left - startbtn.right;
					if (PrintDebugInfo) {
						std::wcout << L"AFTER-WINDOWS-UPDATES-HOTFIX - Taskbar Window Width: " << TaskbarWindowWidth << L". Taskbar Window Rect: " << rect.left << ":" << rect.right << L":" << rect.bottom << L":" << rect.top << "\n";
					}*/
					///END OF TEEEEEEEEEEEST


					DefaultTaskbarIconWidth_Now = DefaultTaskbarIconWidth;
					if (AutoDetectedSingleIconWidthChangeOffsetOnMSTaskSwWClassWindow) {
						DefaultTaskbarIconWidth_Now = AutoDetectedSingleIconWidthChangeOffsetOnMSTaskSwWClassWindow;
					}

					NumberOfItemsOnTaskbar = TaskbarWindowWidth / DefaultTaskbarIconWidth_Now;

					if (PrintDebugInfo) {
						std::wcout << L"Number of icons on taskbar: " << NumberOfItemsOnTaskbar << L". DefaultTaskbarIconWidth_Now: " << DefaultTaskbarIconWidth_Now << L".\n";
					}

					bool DeterminedNumberOfIconsUsingNewMethod = false;
					TaskbarIconInfo newTaskbarIconInfo;
					if (UseTheNewIconsCountingMethod) {
						newTaskbarIconInfo = GetNumberOfIconsAndCalculateWidth();
						if (PrintDebugInfo) {
							std::wcout << L"New_Get_Number_of_Icons_on_Taskbar_After_Updates_Broke_It() returned: " << newTaskbarIconInfo.numberOfIcons << L".\n";
							std::wcout << L"Taskbar icons width: " << newTaskbarIconInfo.totalWidth << L".\n";
						}
						if (newTaskbarIconInfo.numberOfIcons != -1) {
							DeterminedNumberOfIconsUsingNewMethod = true;
							NumberOfItemsOnTaskbar = newTaskbarIconInfo.numberOfIcons;

							rect.left = newTaskbarIconInfo.firstIconX;
							rect.right = newTaskbarIconInfo.lastIconXPlusWidth;
							rect.top = newTaskbarIconInfo.leftMostIcon.y;/// ????
							rect.bottom = newTaskbarIconInfo.leftMostIcon.y + newTaskbarIconInfo.leftMostIcon.height;///???
							TaskbarWindowWidth = newTaskbarIconInfo.totalWidth;
							DefaultTaskbarIconWidth_Now = newTaskbarIconInfo.singleIconWidth;
							if (PrintDebugInfo) {
								std::cout << "rect.left: " << rect.left << std::endl;
								std::cout << "rect.right: " << rect.right << std::endl;
								std::cout << "Left most icon X: " << newTaskbarIconInfo.leftMostIcon.x << std::endl;
								std::cout << "Left most icon Width: " << newTaskbarIconInfo.leftMostIcon.width << std::endl;
								std::wcout << L"Updated Taskbar Window Width (workaround): " << TaskbarWindowWidth << L"\n";
								std::wcout << L"Updated Taskbar Window Rect: " << rect.left << L":" << rect.right << L":" << rect.bottom << L":" << rect.top << L"\n";
							}
						}
					}

					/*if (FixNumberOfIconsOnTaskbarAddOffset != 0) {
						NumberOfItemsOnTaskbar = NumberOfItemsOnTaskbar + FixNumberOfIconsOnTaskbarAddOffset;
						TaskbarWindowWidth = TaskbarWindowWidth + (FixNumberOfIconsOnTaskbarAddOffset * DefaultTaskbarIconWidth_Now);
						if (PrintDebugInfo) {
							std::wcout << L"Config variable \"FixNumberOfIconsOnTaskbarAddOffset\" was set to: " << FixNumberOfIconsOnTaskbarAddOffset << ". Adjusting...\n";
							std::wcout << L"NEW Number of icons on taskbar: " << NumberOfItemsOnTaskbar << L". Adjusted TaskbarWindowWidth: " << TaskbarWindowWidth << "\n";

							wchar_t ActiveWindowBeforeText[MAX_PATH];
							wchar_t ActiveWindowBeforeClassName[MAX_PATH];
							SendMessageW(WindowUnderMouse, WM_GETTEXT, MAX_PATH, (LPARAM)ActiveWindowBeforeText);
							GetClassNameW(WindowUnderMouse, ActiveWindowBeforeClassName, MAX_PATH);
							std::wcout << L"Window under mouse is: " << WindowUnderMouse << L" TITLE: " << ActiveWindowBeforeText << ". CLASS: " << ActiveWindowBeforeClassName << L"\n";
						}
					}*/

					//if (hWndMSTaskSwWClass) {
					if (hWndMSTaskSwWClass) {
						//Check if taskbar area is visible, not to continue when playing games, etc.
						//if (IsWindowVisible(hWndMSTaskSwWClass)) {
						//if (IsWindowVisible(hWndTray)) {
						//For some reasons IsWindowVisible doesn't work as intended, so let's workaround it:

						//ver 2.3.0 window fix moved there:
						if (UseFixForBugAfterSleepMode && !FixForBugAfterSleepModeTestedThisLoop) {
							if (((WindowUnderMouse == hWndMSTaskSwWClass) || ((DeterminedNumberOfIconsUsingNewMethod) && (WindowUnderMouse == hWndTray))) || WindowUnderMouse == hWndTrayNotify || WindowUnderMouse == hWndRebar) {
								FixForBugAfterSleepModeTestedThisLoop = true;
								Last_Step_Reached = 3;
								if (PrimaryScreen.hWndMSTaskSwWClass) {
									if (Fix_Taskbar_Size_Bug(PrimaryScreen.hWndMSTaskSwWClass)) {
										//Fixed. Ignore this loop to get potentially new HWND and RECTs.
										DetectedHWNDsForThisMouseClick = false;//IMPORTANT ver. 1.9.1 to fix program crash after the sleep mode. Also in 2.3 it will reload taskbar sizes.
										AdvancedSleep();
										continue;
									}
								}
							}
						}

						if (((WindowUnderMouse == hWndMSTaskSwWClass) || ((DeterminedNumberOfIconsUsingNewMethod) && (WindowUnderMouse == hWndTray))) || WindowUnderMouse == hWndTrayNotify) {
							if (Last_Step_Reached < 3) {
								Last_Step_Reached = 3;
							}
							//Test pixel check, ver. 2.0.0.0:
							if (DetectKnownPixelColorsToPreventAccidentalEvents) {

								//ver. 2.2 check if "stop" cursor icon instead.
								if (IsCurrentCursorIconStopOrDrag()) {
									DetectedCorrectPixelsInThisClick = true;
								}

								if (!DetectedCorrectPixelsInThisClick) {
									CorrectPixelStatus = CheckControlPixelsAboveTheMouseOnTaskbar();
									if (CorrectPixelStatus > 0) {
										DetectedCorrectPixelsInThisClick = true;
										EVERDetectedCorrectPixels = true;
										if (PrintDebugInfo) {
											std::wcout << L"DetectKnownPixelColorsToPreventAccidentalEvents: Detected CORRECT pixel status: " << CorrectPixelStatus << L". Continuing..." << endl;
										}
									}
									else {
										if (PrintDebugInfo) {
											std::wcout << L"DetectKnownPixelColorsToPreventAccidentalEvents: Detected INCORRECT pixel status: " << CorrectPixelStatus << L". Ignoring the loop..." << endl;
										}
									}
									//ver. 2.2
									if (!CorrectPixelsEverDetectedUsingCookieFile) {
										if (DetectedCorrectPixelsInThisClick && (CorrectPixelStatus == 1)) { // So it wont create a file if different monitor was used and function ignored.
											CorrectPixelsEverDetectedUsingCookieFile = true;
											if (KnownPixelColors_CookieFileCreate()) {
												if (PrintDebugInfo) {
													std::wcout << L"DetectKnownPixelColorsToPreventAccidentalEvents: SUCCESSFULLY created Tmp File..." << endl;
												}
											}
											else {
												if (PrintDebugInfo) {
													std::wcout << L"DetectKnownPixelColorsToPreventAccidentalEvents: FAILED to create Tmp File..." << endl;
												}
											}
										}
									}
								}

								// 
								//Hotfix. If somebody uses different curosr styles, or some icons modifications that make pixels detection impossible, then behave as if DetectKnownPixelColorsToPreventAccidentalEvents was false. So always after program restart... or no thats a bad idea. Might be annoying for people working in Word since computer start.
								// TODO some different detection.
								//if (EVERDetectedCorrectPixels) {
								if (CorrectPixelsEverDetectedUsingCookieFile) {
									if (!DetectedCorrectPixelsInThisClick) {
										AdvancedSleep();
										continue;
									}
								}
								else {
									std::wcout << L"DetectKnownPixelColorsToPreventAccidentalEvents: CorrectPixelsEverDetectedUsingCookieFile is FALSE, so continuing anyway..." << endl;
								}
								//}
							}

							P_Client = P;
							ScreenToClient(hWndMSTaskSwWClass, &P_Client);

							MouseClickStartPoint_Client = MouseClickStartPoint;
							ScreenToClient(hWndMSTaskSwWClass, &MouseClickStartPoint_Client);

							if (MouseClickStartPoint_Client.y >= 0) {
								if (PrintDebugInfo) {
									std::wcout << Current_Button_Name << L" Mouse Click Started in the taskbar area: X: " << MouseClickStartPoint_Client.x << " Y: " << MouseClickStartPoint_Client.y << ", so skipping.\n";
								}
								//The sleep was missing there causing heavy CPU usage. Fixed in ver 1.1.1
								AdvancedSleep();
								continue;
							}

							/*if (MouseClickStartPoint_Client.x >= 0 && MouseClickStartPoint_Client.y >= 0) {
								if (PrintDebugInfo) {
									std::wcout << Current_Button_Name << L" Mouse Click Started in the taskbar area: X: " << MouseClickStartPoint_Client.x << " Y: " << MouseClickStartPoint_Client.y << ", so skipping.\n";
								}
								//The sleep was missing there causing heavy CPU usage. Fixed in ver 1.1.1
								AdvancedSleep();
								continue;
							}*/

							/*if (DetectIfFileIsCurrentlyDraggedUsingClipboard && !Detect_if_Clipboard_Has_Dragged_File_Data()) {
								//Check if currently file is being dragged using clipboard
								if (PrintDebugInfo) {
									std::cout << "No dragged file data type in the clipboard, so skipping.\n";
								}
								Sleep(SleepPeriodNow);
								continue;
							}*/

							if (PrintDebugInfo) {
								std::wcout << L"Client Mouse position. X:" << P_Client.x << L" Y: " << P_Client.y << L"\n";
							}

							//Check if maybe in the "show desktop" area:
							bool ShowDesktopPositionNow = false;
							if (P_Client.y >= 0 && P.x >= ShowDesktopStartPosition) {
								if (WindowsScreenSet == 0) { //To make sure its not secondary screen
									ShowDesktopPositionNow = true;
								}
							}

							int CurrentAppIcon = -1;
							if (DefaultTaskbarIconWidth_Now > 0) {
								CurrentAppIcon = P_Client.x / DefaultTaskbarIconWidth_Now;
							}
							else {
								std::wcout << L"!!! ERROR? DefaultTaskbarIconWidth_Now is 0: " << DefaultTaskbarIconWidth_Now << L" and can't be used for dividing\n";
							}
							int CurrentAppIconPlusOne = CurrentAppIcon + 1;

							if (DeterminedNumberOfIconsUsingNewMethod) {
								int Calc1 = P.x - newTaskbarIconInfo.firstIconX;
								if (P.x >= newTaskbarIconInfo.firstIconX && DefaultTaskbarIconWidth_Now > 0) {
									CurrentAppIcon = Calc1 / DefaultTaskbarIconWidth_Now;
									CurrentAppIconPlusOne = CurrentAppIcon + 1;
								}
								else {
									CurrentAppIcon = -1;
									CurrentAppIconPlusOne + 0;
								}
							}

							if (PrintDebugInfo) {
								std::wcout << L"!!!!! Checking if CurrentAppIcon: " << CurrentAppIcon << L" <  NumberOfItemsOnTaskbar: " << NumberOfItemsOnTaskbar << L". Don't get confused by these numbers.\n";
							}
							//if ((P_Client.x >= 0 && P_Client.y >= 0 && P_Client.x <= TaskbarWindowWidth) || ShowDesktopPositionNow) {
							if ((P_Client.x >= 0 && P_Client.y >= 0 && CurrentAppIcon < NumberOfItemsOnTaskbar && CurrentAppIcon > -1) || ShowDesktopPositionNow) {
								if (Last_Step_Reached < 4) {
									Last_Step_Reached = 4;
								}
								SleepPeriodNow = SleepPeriodWhenMouseIsOnAppIconInTheLoopMilliseconds;
								//std::wcout << L"TEEEEEEEEEEEEEEST 222222222222222" << L".\n";


								if (ShowDesktopPositionNow) {
									CurrentAppIcon = 999;
									CurrentAppIconPlusOne = 1000;
								}

								if (PreviousHoveredMouseAppID != CurrentAppIcon) {
									PreviousHoveredMouseAppID = CurrentAppIcon;
									FirstTimeHoveredOverThisAppIcon = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
								}

								long long int HowLongOverThisIconCount = TimeNow.count() - FirstTimeHoveredOverThisAppIcon.count();

								if (PrintDebugInfo) {
									std::wcout << L"Currently in the taskbar area! App icon ID: " << CurrentAppIconPlusOne << L". Pressed for milliseconds: " << HowLongOverThisIconCount << "\n";
								}

								if (HowLongOverThisIconCount >= HowLongKeepMouseOverAppIconBeforeRestoringWindowMilliseconds) {
									if (Last_Step_Reached < 5) {
										Last_Step_Reached = 5;
									}
									if ((CurrentAppIcon != LastSimulatedHotkeyPressID || UseTheNewBestMethodEver)) { //UseTheNewBestMethodEver might cause a bug bug
										if (Last_Step_Reached < 6) {
											Last_Step_Reached = 6;
										}
										LastSimulatedHotkeyPressID = CurrentAppIcon;
										if (UseTheNewBestMethodEver) {
											if (Last_Step_Reached < 7) {
												Last_Step_Reached = 7;
											}
											//Finally found a perfect solution:
											if (CurrentAppIcon == 999) {
												if (hWndTray) {
													Simulate_Show_Desktop_Behaviour();
													//LRESULT res = SendMessage(hWndTray, WM_COMMAND, (WPARAM)419, 0);
												}
												else {
													//It should never be executed, because hWndTray couldn't be NULL at higher steps...
													//Show desktop thing:
													keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, 0, 0);
													keybd_event(REMAP_VK_D, VIRTUAL_REMAP_VK_D, 0, 0);
													Sleep(50);
													keybd_event(REMAP_VK_D, VIRTUAL_REMAP_VK_D, KEYEVENTF_KEYUP, 0);
													keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, KEYEVENTF_KEYUP, 0);
												}

												if (PrintDebugInfo) {
													std::wcout << L"Simulating Logo Win + " << CurrentAppIconPlusOne << L" key\n";
												}
											}
											else {
												Finally_The_Best_Method_Ever(CurrentAppIcon, NumberOfItemsOnTaskbar, WindowsScreenSet);
											}
										}
										else if (CurrentAppIcon <= 9) {
											if (Last_Step_Reached < 7) {
												Last_Step_Reached = 7;
											}
											if (UseTheNewWMHOTKEYMethod && hWndTray) {
												LRESULT SendMessageReturn = SendMessage(hWndTray, WM_HOTKEY, New_WM_HOTKEY_Array_LogoWin_CTRL_Num[CurrentAppIcon].first, New_WM_HOTKEY_Array_LogoWin_CTRL_Num[CurrentAppIcon].second);
												if (PrintDebugInfo) {
													std::wcout << L"Sending WM_HOTKEY message for Logo Win + CTRL + " << CurrentAppIconPlusOne << L" key\n";
												}
											}
											else {
												keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, 0, 0); //Press windows key
												keybd_event(REMAP_VK_LCONTROL, VIRTUAL_REMAP_VK_LCONTROL, 0, 0); //Press CTRL key
												keybd_event(Keyboard_Keys_One_to_Zero[CurrentAppIcon], MapVirtualKey(Keyboard_Keys_One_to_Zero[CurrentAppIcon], 0), 0, 0);
												Sleep(50);
												keybd_event(Keyboard_Keys_One_to_Zero[CurrentAppIcon], MapVirtualKey(Keyboard_Keys_One_to_Zero[CurrentAppIcon], 0), KEYEVENTF_KEYUP, 0);
												keybd_event(REMAP_VK_LCONTROL, VIRTUAL_REMAP_VK_LCONTROL, KEYEVENTF_KEYUP, 0); // left Release
												keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, KEYEVENTF_KEYUP, 0); // left Release
												if (PrintDebugInfo) {
													std::wcout << L"Simulating Logo Win + CTRL + " << CurrentAppIconPlusOne << L" key\n";
												}
											}

										}
										else if (CurrentAppIcon == 999) {
											if (Last_Step_Reached < 7) {
												Last_Step_Reached = 7;
											}
											if (hWndTray) {
												Simulate_Show_Desktop_Behaviour();
												//LRESULT res = SendMessage(hWndTray, WM_COMMAND, (WPARAM)419, 0);
											}
											else {
												//It should never be executed, because hWndTray couldn't be NULL at higher steps...
												//Show desktop thing:
												keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, 0, 0);
												keybd_event(REMAP_VK_D, VIRTUAL_REMAP_VK_D, 0, 0);
												Sleep(50);
												keybd_event(REMAP_VK_D, VIRTUAL_REMAP_VK_D, KEYEVENTF_KEYUP, 0);
												keybd_event(REMAP_VK_LWIN, VIRTUAL_REMAP_VK_LWIN, KEYEVENTF_KEYUP, 0);
											}

											if (PrintDebugInfo) {
												std::wcout << L"Simulating Logo Win + " << CurrentAppIconPlusOne << L" key\n";
											}
										}

										#ifndef DONT_INCLUDE_UNUSED_FUNCTIONS_TO_PREVENT_PSEUDO_ANTIVIRUSES_FROM_THROWING_FALSE_POSITIVES
										else if (CurrentAppIcon > 9) {
											if (UseTheNewWorkaroundForButtonsElevenPlus) {
												Experimental_Workaround_for_buttons_Eleven_Plus();
											}
										}
										#endif
										else {
											if (PrintDebugInfo) {
												std::wcout << L"Unfortunately, can't restore the window because App icon ID is greater than 10 :(\n";
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
			AdvancedSleep();
		}
		catch (...) {
			//In case program crashes restart it automatically, but not more than 100 times.
			if (RestartedCrashedTimes < 101) {
				RestartedCrashedTimes++;
				RestartExtraWstring = L"-restarted-times-" + to_wstring(RestartedCrashedTimes) + L"-";
				InterruptMainThread = true;
				InterruptRestartProgram = true;

			}
			else {
				InterruptMainThread = true;
				InterruptRestartProgram = false;
			}
			break;
		}
	}

	if (InterruptRestartProgram) {
		wstring RestartNowWstr = L"restart-ignore-mutex" + RestartExtraWstring;
		if (!InterruptRestartProgramRunAs) {
			ShellExecuteW(NULL, L"open", CurrentExeWorks.c_str(), RestartNowWstr.c_str(), NULL, SW_SHOW);
		}
		else {
			ShellExecuteW(NULL, L"runas", CurrentExeWorks.c_str(), RestartNowWstr.c_str(), NULL, SW_SHOW);
		}
	}

	return 0;
}

void ClickedOpenPathFromTray() {
	ShellExecuteW(NULL, L"open", CurrentExeWorksPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void ClickedChangelogFromTray() {
	ShellExecuteW(NULL, L"open", GitHubChangeLog.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void ClickedAboutFromTray() {
	ShellExecuteW(NULL, L"open", GitHubAbout.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void ClickedCheckForUpdatesFromTray() {
	ShellExecuteW(NULL, L"open", GitHubReleases.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void ClickedConfigureFromTray() {
	if (!FileExistsW(ConfigFileBase.c_str())) {
		std::ofstream ofs(ConfigFileBase.c_str(), std::ofstream::out);
		ofs << "//Should the program run automatically on system startup? 1 = true, 0 = false." << endl
			<< "AutomaticallyRunThisProgramOnStartup=1" << endl << "StartThisProgramAsAdministrator=0" << endl << endl << "//For more configuration options, please visit: https://github.com/HerMajestyDrMona/Windows11DragAndDropToTaskbarFix/blob/main/CONFIGURATION.md" << endl;
		ofs.close();
		if (FileExistsW(ConfigFileBase.c_str())) {
			LastSettingsChangeTime = ReturnConfigFileTime();
		}
	}
	if (FileExistsW(ConfigFileBase.c_str())) {
		if (ShExecInfo.hProcess != 0) {
			if (WaitForSingleObject(ShExecInfo.hProcess, 1) == WAIT_TIMEOUT) {
				return;
			}
			else {
				CloseHandle(ShExecInfo.hProcess);
			}
		}

		ShellExecuteW(NULL, L"open", GitHubConfiguration.c_str(), NULL, NULL, SW_SHOWNORMAL);

		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		//ShExecInfo.lpVerb = L"edit";
		//ver 1.9.0, so can open in Notepad++
		ShExecInfo.lpVerb = L"open";
		ShExecInfo.lpFile = ConfigFileBase.c_str();
		ShExecInfo.lpParameters = L"";
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_SHOWNORMAL;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		if (ShExecInfo.hProcess != 0) {
			EnableMenuItem(Hmenu, ConfigButtonID, MF_DISABLED | MF_GRAYED | MF_BYPOSITION);
			SendMessage(Hwnd, WM_NULL, 0, 0);
			ConfigMenuDisabled = true;
			//WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
			if (WaitForSingleObject(ShExecInfo.hProcess, 1) == WAIT_TIMEOUT) {

			}
			//CloseHandle(ShExecInfo.hProcess);
		}
	}
	else {
		//Error pls run as admin
		wstring RunasTitie = L"Windows11DragAndDropToTaskbarFix.exe by Dr.MonaLisa:";
		wstring RunasQuestion = L"Failed to create the configuration file: \"" + ConfigFileBase + L"\".\n\nWould you like to re-launch Windows11DragAndDropToTaskbarFix as administrator in order to grant the write permissions?\n\n- Click \"YES\" to restart the program as administrator.\n\n- Click \"NO\" to ignore and continue without changing the configuration.";
		int RunAsQuestionint = MessageBoxW(NULL, RunasQuestion.c_str(), RunasTitie.c_str(), MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST | MB_SETFOREGROUND | MB_DEFBUTTON1);
		if (RunAsQuestionint == IDYES) {
			if (Hwnd) {
				if (ShowTrayIcon) {
					Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
				}
				SendMessage(Hwnd, WM_NULL, 0, 0);
				SendMessage(Hwnd, WM_DESTROY, 0, 0);
			}
			InterruptMouseWatchdogThread = true;
			InterruptRestartProgram = true;
			InterruptRestartProgramRunAs = true;
			InterruptMainThread = true;
		}
		else {
			ShellExecuteW(NULL, L"open", GitHubConfiguration.c_str(), NULL, NULL, SW_SHOWNORMAL);
		}
	}
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_TASKBAR && !IsWindowVisible(Hwnd))
	{
		minimize();
		return 0;
	}

	switch (message)
	{
	case WM_ACTIVATE:
		//Shell_NotifyIcon(NIM_ADD, &notifyIconData);
		break;
	case WM_CREATE:
		ShowWindow(Hwnd, SW_HIDE);

		if (ShowTrayIcon) {
			Hmenu = CreatePopupMenu();
			NameAndVer = L"Windows 11 Drag && Drop to the Taskbar (Fix)";
			NameAndVer2 = L"ver. " + ProgramVersion + L". Created by Dr. Mona Lisa.";
			NameRestart = L"Restart (PID: " + to_wstring(CurrentProcessID) + L")";
			if (!TheProgramIsRunningAsAdministratorRightNow) {
				NameRestart = L"* Restart (PID: " + to_wstring(CurrentProcessID) + L")";
			}
			if (RestartedCrashedTimes == 1) {
				NameRestart = NameRestart + L" [Crashed: " + to_wstring(RestartedCrashedTimes) + L" time]...";
			}
			else if (RestartedCrashedTimes > 0) {
				NameRestart = NameRestart + L" [Crashed:" + to_wstring(RestartedCrashedTimes) + L" times]...";
			}
			NameRestart = NameRestart + L"...";
			NameRestartAsAdmin = L"Restart as administrator...";
			if (TheProgramIsRunningAsAdministratorRightNow) {
				NameRestartAsAdmin = L"* Restart as administrator...";
			}

			AppendMenuW(Hmenu, MF_MENUBREAK, 0, NULL);
			//AppendMenu(Hmenu, MF_BITMAP, 2, (LPCTSTR)hbitmap);
			AppendMenuW(Hmenu, MF_STRING, ID_TRAY_ABOUT, NameAndVer.c_str());
			AppendMenuW(Hmenu, MF_STRING, ID_TRAY_ABOUT, NameAndVer2.c_str());
			AppendMenuW(Hmenu, MF_SEPARATOR, 0, NULL);
			//AppendMenuW(Hmenu, MF_STRING, ID_TRAY_ABOUT, L"About...");
			AppendMenuW(Hmenu, MF_STRING, ID_TRAY_CHECKUPDATES, L"Check for updates...");
			AppendMenuW(Hmenu, MF_STRING, ID_TRAY_CHANGELOG, L"Read the changelog...");
			AppendMenuW(Hmenu, MF_STRING, ID_TRAY_CONFIGURE, L"Configure...");
			AppendMenuW(Hmenu, MF_SEPARATOR, 0, NULL);
			AppendMenuW(Hmenu, MF_STRING, ID_TRAY_OPENPATH, L"Open program folder...");
			AppendMenuW(Hmenu, MF_STRING, ID_TRAY_RESTART, NameRestart.c_str());
			AppendMenuW(Hmenu, MF_STRING, ID_TRAY_RESTARTADMIN, NameRestartAsAdmin.c_str());
			AppendMenuW(Hmenu, MF_STRING, ID_TRAY_EXIT, L"Quit...");
			AppendMenuW(Hmenu, MF_MENUBREAK, 0, NULL);
			//Make some texts bold:
			ZeroMemory(&ItemInfo, sizeof(ItemInfo));
			ItemInfo.cbSize = sizeof(ItemInfo);
			GetMenuItemInfo(Hmenu, 1, TRUE, &ItemInfo);
			ItemInfo.fMask = MIIM_STATE;
			ItemInfo.fState = MFS_ENABLED | MFS_DEFAULT;
			SetMenuItemInfo(Hmenu, 1, TRUE, &ItemInfo);
			GetMenuItemInfo(Hmenu, 2, TRUE, &ItemInfo);
			ItemInfo.fMask = MIIM_STATE;
			ItemInfo.fState = MFS_ENABLED | MFS_DEFAULT;
			SetMenuItemInfo(Hmenu, 2, TRUE, &ItemInfo);
		}
		break;

	case WM_SYSCOMMAND:
		switch (wParam & 0xFFF0)
		{
		case SC_MINIMIZE:
		case SC_CLOSE:
			minimize();
			return 0;
			break;
		}
		break;

	case WM_SYSICON:
	{
		if (!ShowTrayIcon) {
			break;
		}

		switch (wParam)
		{
		case ID_TRAY_APP_ICON:
			SetForegroundWindow(Hwnd);

			break;
		}
		/*if (lParam == WM_LBUTTONUP)
		{

			restore();
		}
		else*/ 
		if (lParam == WM_LBUTTONUP || lParam == WM_RBUTTONDOWN)
		{
			if (ConfigMenuDisabled) {
				if (ShExecInfo.hProcess != 0) {
					if (WaitForSingleObject(ShExecInfo.hProcess, 1) == WAIT_TIMEOUT) {

					}
					else {
						EnableMenuItem(Hmenu, ConfigButtonID, MF_ENABLED | MF_BYPOSITION);
						SendMessage(Hwnd, WM_NULL, 0, 0);
						ConfigMenuDisabled = false;

						CloseHandle(ShExecInfo.hProcess);
						ShExecInfo.hProcess = 0;
					}
				}
			}

			// Get current mouse position.
			POINT curPoint;
			GetCursorPos(&curPoint);
			SetForegroundWindow(Hwnd);

			// TrackPopupMenu blocks the app until TrackPopupMenu returns

			UINT clicked = TrackPopupMenu(Hmenu, TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, 0, hwnd, NULL);

			SendMessage(hwnd, WM_NULL, 0, 0); // send benign message to window to make sure the menu goes away.
			switch (clicked)
			{
				case ID_TRAY_EXIT: {
					// quit the application.
					if (ShowTrayIcon) {
						Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
					}

					//Terminate other threads.
					InterruptMouseWatchdogThread = true;
					InterruptMainThread = true;
					PostQuitMessage(0);
					break;
				}
				case ID_TRAY_SHOW: {
					restore();
					break;
				}
				case ID_TRAY_RESTART: {
					if (ShowTrayIcon) {
						Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
					}

					InterruptMouseWatchdogThread = true;
					//NewFunctionToKill(true);
					InterruptRestartProgram = true;
					InterruptMainThread = true;
					PostQuitMessage(0);
					break;
				}
				case ID_TRAY_RESTARTADMIN: {
					if (ShowTrayIcon) {
						Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
					}
					InterruptRestartProgramRunAs = true;
					InterruptMouseWatchdogThread = true;
					InterruptRestartProgram = true;
					InterruptMainThread = true;
					PostQuitMessage(0);
					break;
				}
				case ID_TRAY_CONFIGURE: {
					ClickedConfigureFromTray();
					break;
				}
				case ID_TRAY_CHECKUPDATES: {
					ClickedCheckForUpdatesFromTray();
					break;
				}
				case ID_TRAY_ABOUT: {
					ClickedAboutFromTray();
					break;
				}
				case ID_TRAY_CHANGELOG: {
					ClickedChangelogFromTray();
					break;
				}
				case ID_TRAY_OPENPATH: {
					ClickedOpenPathFromTray();
					break;
				}
			}

		}
	}
	break;

	case WM_NCHITTEST:
	{
		LRESULT uHitTest = DefWindowProc(hwnd, WM_NCHITTEST, wParam, lParam);
		if (uHitTest == HTCLIENT)
			return HTCAPTION;
		else
			return uHitTest;
	}

	case WM_CLOSE:

		minimize();
		return 0;
		break;

	case WM_DESTROY:
		InterruptMouseWatchdogThread = true;
		InterruptMainThread = true;
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

void minimize()
{
	ShowWindow(Hwnd, SW_HIDE);
}

void restore()
{
	ShowWindow(Hwnd, SW_SHOW);
}

void InitNotifyIconData()
{
	memset(&notifyIconData, 0, sizeof(NOTIFYICONDATA));
	notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
	notifyIconData.hWnd = Hwnd;
	notifyIconData.uID = ID_TRAY_APP_ICON;
	notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notifyIconData.uCallbackMessage = WM_SYSICON; //Set up our invented Windows Message
	if (!UseAlternativeTrayIcon) {
		notifyIconData.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	}
	else {
		notifyIconData.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
	}
	wcsncpy_s(notifyIconData.szTip, szTIP, sizeof(szTIP));
}

//Unused functions, might use something from it in the future, so not deleting it yet.
#ifndef DONT_INCLUDE_UNUSED_FUNCTIONS_TO_PREVENT_PSEUDO_ANTIVIRUSES_FROM_THROWING_FALSE_POSITIVES

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
		std::size_t Test1 = FavouritesData.find(L".lnk", 0, LastBufferSize);
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

HWND Wait_For_The_New_Active_Window(HWND& ActiveWindowBeforeClickingOnAppIcon, wstring DebugStep) {

	//Hotfix:
	HWND ProgManHWND = FindWindow(L"Progman", nullptr);
	if (PrintDebugInfo) {
		std::wcout << L"Found Progman window HWND: " << ProgManHWND << endl;
	}

	//Wait for the new Active Window:
	std::chrono::milliseconds SleepFor(SleepTimeButtonsElevenPlusMilliseconds);

	bool FoundNewActiveWindow = false;
	HWND ActiveWindowNow = NULL;
	HWND ActiveWindowNowToReturn = NULL;

	std::chrono::milliseconds StartedTheLoopAt = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	long long int StartedTheLoopAtCountPlus = StartedTheLoopAt.count() + CheckForNewActiveWindowForButtonsElevenPlusMilliseconds;

	while (true) {
		std::chrono::milliseconds TimeAtTheLoopNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		//ActiveWindowNow = GetActiveWindow();
		//ActiveWindowNow = GetTopWindow(NULL);
		ActiveWindowNow = GetForegroundWindow();
		if (ActiveWindowNow) {
			if (ActiveWindowNow != ProgManHWND && ActiveWindowNow != ActiveWindowBeforeClickingOnAppIcon) {
				if (IsWindowVisible(ActiveWindowNow)) {
					FoundNewActiveWindow = true;
					ActiveWindowNowToReturn = ActiveWindowNow;
					break;
				}
			}
		}
		if (TimeAtTheLoopNow.count() >= StartedTheLoopAtCountPlus) {
			if (PrintDebugInfo) {
				long long int Difference = TimeAtTheLoopNow.count() - StartedTheLoopAt.count();
				std::wcout << L"Unfortunately, the Wait_For_The_New_Active_Window() loop has timeouted after: " << Difference << L" ms." << endl;
			}
			break;
		}
		std::this_thread::sleep_for(SleepFor);
	}

	//This one sleeps for too long. Not a good method.
	/*for (int iii = 0; iii < NumberOfAttemptsInThisLoop; iii++) {
		ActiveWindowNow = GetActiveWindow();
		if (ActiveWindowNow) {
			if (ActiveWindowNow != ActiveWindowBeforeClickingOnAppIcon) {
				FoundNewActiveWindow = true;
				break;
			}
		}
		std::this_thread::sleep_for(SleepFor);
	}*/

	if (PrintDebugInfo) {
		wchar_t ActiveWindowBeforeText[MAX_PATH];
		wchar_t ActiveWindowBeforeClassName[MAX_PATH];
		wchar_t ActiveWindowAfterText[MAX_PATH];
		wchar_t ActiveWindowAfterTextClassName[MAX_PATH];
		SendMessageW(ActiveWindowBeforeClickingOnAppIcon, WM_GETTEXT, MAX_PATH, (LPARAM)ActiveWindowBeforeText);
		SendMessageW(ActiveWindowNow, WM_GETTEXT, MAX_PATH, (LPARAM)ActiveWindowAfterText);
		GetClassNameW(ActiveWindowBeforeClickingOnAppIcon, ActiveWindowBeforeClassName, MAX_PATH);
		GetClassNameW(ActiveWindowNow, ActiveWindowAfterTextClassName, MAX_PATH);

		std::wcout << DebugStep << L". ActiveWindowBefore: " << ActiveWindowBeforeClickingOnAppIcon << L" (" << ActiveWindowBeforeText << L")" << L" (" << ActiveWindowBeforeClassName << L")" << L". ActiveWindowNow: " << ActiveWindowNow << " (" << ActiveWindowAfterText << L")" << " (" << ActiveWindowAfterTextClassName << L"). Returning: " << ActiveWindowNowToReturn << endl;
	}

	return ActiveWindowNowToReturn;
}

bool Wait_For_Following_Window_To_Become_Foreground_Under_Mouse(HWND& ActiveWindowBeforeClickingOnAppIcon) {
	std::chrono::milliseconds SleepFor(SleepTimeButtonsElevenPlusMilliseconds);
	std::chrono::milliseconds StartedTheLoopAt = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	long long int StartedTheLoopAtCountPlus = StartedTheLoopAt.count() + CheckForNewActiveWindowForButtonsElevenPlusMilliseconds;
	HWND ActiveWindowNow = NULL;
	HWND TmpWindowFromPoint = NULL;
	while (true) {
		std::chrono::milliseconds TimeAtTheLoopNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		ActiveWindowNow = WindowFromPoint(MouseClickStartPointCopy);
		if (ActiveWindowNow) {
			if (ActiveWindowNow == ActiveWindowBeforeClickingOnAppIcon) {
				if (IsWindowVisible(ActiveWindowNow)) {
					return true;
					break;
				}
			}
		}
		if (TimeAtTheLoopNow.count() >= StartedTheLoopAtCountPlus) {
			if (PrintDebugInfo) {
				wchar_t ActiveWindowAfterText[MAX_PATH];
				wchar_t ActiveWindowAfterTextClassName[MAX_PATH];
				SendMessageW(ActiveWindowNow, WM_GETTEXT, MAX_PATH, (LPARAM)ActiveWindowAfterText);
				GetClassNameW(ActiveWindowNow, ActiveWindowAfterTextClassName, MAX_PATH);

				long long int Difference = TimeAtTheLoopNow.count() - StartedTheLoopAt.count();
				std::wcout << L"Unfortunately, the Wait_For_Following_Window_To_Become_Foreground_Under_Mouse() loop has timeouted after: " << Difference << L" ms. Last window: " << ActiveWindowNow << L" " << ActiveWindowAfterText << L" (" << ActiveWindowAfterTextClassName << L")" << endl;
			}
			break;
		}
		std::this_thread::sleep_for(SleepFor);
	}

	return false;
}

void Experimental_Workaround_for_buttons_Eleven_Plus() {
	//Experimental Workaround Clicks the icon and returns to the previous state.

	HWND destop = GetDesktopWindow();
	HWND hWorkerW = NULL;
	HWND hShellViewWin = NULL;
	do
	{
		hWorkerW = FindWindowEx(destop, hWorkerW, L"WorkerW", NULL);
		hShellViewWin = FindWindowEx(hWorkerW, 0, L"SHELLDLL_DefView", 0);
	} while (hShellViewWin == NULL && hWorkerW != NULL);

	//FolderViewWindow is used to determine if something was dragged from the Desktop window
	HWND FolderViewWindow = FindWindowEx(hShellViewWin, 0, L"SysListView32", nullptr);

	bool StillSameSession = false;
	if (Last_UniqueID_session_of_Experimental_Workaround == Current_UniqueID_of_the_click) {
		//Use old Start Click Point
		StillSameSession = true;
		if (PrintDebugInfo) {
			std::wcout << L"Still the same session in Experimental_Workaround_for_buttons_Eleven_Plus()." << endl;
		}
	}
	else {
		MouseClickStartPointCopy = MouseClickStartPoint;
		StillSameSession = false;

		FirstWindowWhereDragged = WindowFromPoint(MouseClickStartPointCopy);
		if (FirstWindowWhereDragged == FolderViewWindow) {
			if (PrintDebugInfo) {
				std::wcout << L"It's desktop window!" << endl;
			}
			ItWasDesktopWindow = true;
		}
		else {
			if (PrintDebugInfo) {
				std::wcout << L"It's not a desktop window!" << endl;
			}
			ItWasDesktopWindow = false;
		}

		if (PrintDebugInfo) {
			wchar_t ActiveWindowBeforeText[MAX_PATH];
			wchar_t ActiveWindowBeforeClassName[MAX_PATH];
			SendMessageW(FirstWindowWhereDragged, WM_GETTEXT, MAX_PATH, (LPARAM)ActiveWindowBeforeText);
			GetClassNameW(FirstWindowWhereDragged, ActiveWindowBeforeClassName, MAX_PATH);

			std::wcout << L"FirstWindowWhereDragged INFO: " << FirstWindowWhereDragged << L" " << ActiveWindowBeforeText << L" (" << ActiveWindowBeforeClassName << L")" << endl;
		}
	}

	Last_UniqueID_session_of_Experimental_Workaround = Current_UniqueID_of_the_click;

	int screenX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int screenY = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	if (StillSameSession) {
		if (ItWasDesktopWindow) {
			Simulate_Show_Desktop_Behaviour();
		}
		//Try to restore original window:
		else {
			SetForegroundWindow(FirstWindowWhereDragged);
			SetActiveWindow(FirstWindowWhereDragged);
			SetFocus(FirstWindowWhereDragged);
		}

		//Wait for Window to become foreground under mouse.
		//Note, it works bad for the Desktop window, so we avoid it.
		if (!ItWasDesktopWindow && Wait_For_Following_Window_To_Become_Foreground_Under_Mouse(FirstWindowWhereDragged)) {
			if (PrintDebugInfo) {
				std::wcout << L"Good. Wait_For_Following_Window_To_Become_Foreground() returned true." << endl;
			}
		}

		//Unfortunately, we still need some short (or long?) sleep here, so other windows have time to hide.
		Sleep(AnimationLagButtonsElevenPlusMilliseconds);

	}

	//Get mouse position now on taskbar:
	POINT MousePositionNowOnTaskbar;
	GetCursorPos(&MousePositionNowOnTaskbar);

	INPUT inputt = { 0 };
	inputt.mi.dx = MousePositionNowOnTaskbar.x * (65535 / screenX);
	inputt.mi.dy = MousePositionNowOnTaskbar.y * (65535 / screenY);
	//inputt.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_LEFTDOWN;
	inputt.type = INPUT_MOUSE;

	//HWND ActiveWindowBeforeClickingOnAppIcon = GetActiveWindow();
	//HWND ActiveWindowBeforeClickingOnAppIcon = GetTopWindow(NULL);
	HWND ActiveWindowBeforeClickingOnAppIcon = GetForegroundWindow();

	//Inform the LowLevelMousePressProc not to update the Unique ID for the left mouse button.
	//It's because we don't want to repeat the same function on the same button. It's just a hotfix:
	LLMP_Temporarily_Dont_Update_UniqueID = true;

	//Release the left mouse click together with the dragged item:
	inputt.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_LEFTUP;
	SendInput(1, &inputt, sizeof INPUT);
	//Sleep(10);
	//Press the left mouse button in order to open the window under it:
	inputt.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &inputt, sizeof INPUT);
	//Sleep(10);
	//Release the left mouse button
	inputt.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_LEFTUP;
	SendInput(1, &inputt, sizeof INPUT);

	HWND ActiveWindowNow = Wait_For_The_New_Active_Window(ActiveWindowBeforeClickingOnAppIcon, L"Step 1");

	if (ActiveWindowNow) {
		//Unfortunately, we still need some short (or long?) sleep here, so other windows have time to hide.
		Sleep(AnimationLagButtonsElevenPlusMilliseconds);

		HWND ActiveWindowNextOne = GetForegroundWindow();

		//Return to original window:
		if (ItWasDesktopWindow) {
			if (PrintDebugInfo) {
				std::wcout << L"It was a desktop window, so calling Simulate_Show_Desktop_Behaviour()" << endl;
			}
			Simulate_Show_Desktop_Behaviour();

			//Hope it fixes detection
			SetForegroundWindow(FirstWindowWhereDragged);
			SetActiveWindow(FirstWindowWhereDragged);
			SetFocus(FirstWindowWhereDragged);
		}
		else {
			//ALT + TAB is more reliable method
			if (PrintDebugInfo) {
				std::wcout << L"It wasn't desktop, so calling Simulate_ALT_Plus_TAB_Hotkey()" << endl;
			}
			Simulate_ALT_Plus_TAB_Hotkey();

			//Hope it fixes detection
			SetForegroundWindow(FirstWindowWhereDragged);
			SetActiveWindow(FirstWindowWhereDragged);
			SetFocus(FirstWindowWhereDragged);
		}

		//Sleep(10);
		//Sleep(250);
		//Sleep(250);

		//Wait again for window change:
		HWND ActiveWindowNow2 = Wait_For_The_New_Active_Window(ActiveWindowNextOne, L"Step 2");

		if (ActiveWindowNow2) {
			//Unfortunately, we still need some short (or long?) sleep here, so other windows have time to hide.
			Sleep(AnimationLagButtonsElevenPlusMilliseconds);

			HWND ActiveWindowNextOne2 = GetForegroundWindow();

			//Move mouse to the previous location where the left mouse button was clicked to start dragging the file.
			inputt.mi.dx = MouseClickStartPointCopy.x * (65535 / screenX);
			inputt.mi.dy = MouseClickStartPointCopy.y * (65535 / screenY);
			inputt.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_MOVE;
			SendInput(1, &inputt, sizeof INPUT);
			//Sleep(10);

			//Press the left mouse button down in order to start dragging again:
			inputt.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &inputt, sizeof INPUT);

			//Sleep(10);

			//Move the mouse to the last position on the taskbar not to make users confused (or to make them more confused):
			inputt.mi.dx = MousePositionNowOnTaskbar.x * (65535 / screenX);
			inputt.mi.dy = MousePositionNowOnTaskbar.y * (65535 / screenY);
			inputt.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_MOVE;
			SendInput(1, &inputt, sizeof INPUT);

			Simulate_ALT_Plus_TAB_Hotkey();

			//Confirm that window re-appeared:

			if (PrintDebugInfo) {
				HWND ActiveWindowNow3 = Wait_For_The_New_Active_Window(ActiveWindowNextOne2, L"Step 3");
				if (ActiveWindowNow3) {
					if (PrintDebugInfo) {
						std::wcout << L"Window " << ActiveWindowNow3 << L" re-appeared successfully." << endl;
					}
				}
			}

			//}

		}
	}

	//Restore the default Unique ID behaviour in LowLevelMousePressProc:
	LLMP_Temporarily_Dont_Update_UniqueID = false;
}

bool Detect_if_Clipboard_Has_Dragged_File_Data() {
	WORD m_cfHIDA = (CLIPFORMAT)RegisterClipboardFormat(CFSTR_SHELLIDLIST);
	std::wcout << L"Drag format should be: " << m_cfHIDA << endl;

	LPDATAOBJECT lpDataObject;

	HRESULT OleClipboard = OleGetClipboard(&lpDataObject);
	if (OleClipboard == S_OK) {
		LPENUMFORMATETC lpEnumFORMATETC;

		if (lpDataObject->EnumFormatEtc(DATADIR_GET, &lpEnumFORMATETC) != S_OK) {
			std::wcout << L"Failed to EnumFormatEtc" << endl;
			Unique_ID_of_Click_with_File_NOT_Dragged = Current_UniqueID_of_the_click;
			return false;
		}
		if (lpEnumFORMATETC == NULL) {
			std::wcout << L"Error. lpEnumFORMATETC is NULL" << endl;
			Unique_ID_of_Click_with_File_NOT_Dragged = Current_UniqueID_of_the_click;
			return false;
		}

		FORMATETC formatEtc;

		while (lpEnumFORMATETC->Next(1, &formatEtc, NULL) == S_OK)
		{
			//formatEtc
			std::wcout << L"Format: " << formatEtc.cfFormat << endl;
			//if (formatEtc.cfFormat == CFSTR_SHELLIDLIST) {

			//}

			STGMEDIUM stgMedium;
			if (lpDataObject->GetData(&formatEtc, &stgMedium) != S_OK)
			{
				// data is not available
				CoTaskMemFree(formatEtc.ptd);
			}
			else if (stgMedium.pUnkForRelease != NULL)
			{
				// don't cache data with pUnkForRelease != NULL
				::ReleaseStgMedium(&stgMedium);
				CoTaskMemFree(formatEtc.ptd);
			}
			else
			{
				//std::wcout << L"Filename: " << stgMedium.hGlobal << endl;

				// cache the data (now we own the stgMedium)
				//pDataSource->CacheData(0, &stgMedium, &formatEtc);
			}
		}

		std::wcout << L"Done" << endl;

		// cleanup
		lpEnumFORMATETC->Release();

	}
	else {
		//No need.
	}

	return false;
}

void TestCall() {
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);

	while (true) {
		Detect_if_Clipboard_Has_Dragged_File_Data();
		Sleep(3000);
	}
}

/*vector <wstring> CurrentVisibleWindows;
vector <wstring> PreviousVisibleWindows;

static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
	wchar_t Buffor[MAX_PATH];
	GetClassNameW(hWnd, Buffor, MAX_PATH);

	wstring ClassName = L"UNKNOWN";
	if (wcslen(Buffor) > 1) {
		ClassName = Buffor;
	}
	if (IsWindowVisible(hWnd)) {
		ClassName = ClassName + L"_Visible";
	}
	else {
		ClassName = ClassName + L"_Invisible";
	}
	RECT rectTest;
	GetWindowRect(hWnd, &rectTest);
	wstring RectStr = L"_left" + to_wstring(rectTest.left) + L"_right" + to_wstring(rectTest.right) + L"_bottom" + to_wstring(rectTest.bottom) + L"_top" + to_wstring(rectTest.top);

	ClassName = ClassName + L"_" + RectStr + L"_" + std::to_wstring((DWORD)hWnd);
	CurrentVisibleWindows.push_back(ClassName);

	//Child windows:
	EnumChildWindows(hWnd, enumWindowCallback, NULL);

	return TRUE;
}

void TestErrorIconDetection() {
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);

	while (true) {

		HWND ErrorIcon = FindWindowEx(NULL, 0, L"SysDragImage", nullptr);
		if (ErrorIcon) {
			std::wcout << L"SysDragImage window is was WAS found:" << ErrorIcon << endl;
			if (IsWindowVisible(ErrorIcon)) {
				std::wcout << L"SysDragImage window is VISIBLE." << endl;
			}
			else {
				std::wcout << L"SysDragImage window is INVISIBLE." << endl;
			}
		}
		else {
			std::wcout << L"SysDragImage window is was NOT found." << endl;
		}


		Sleep(1000);
		continue;

		CurrentVisibleWindows.clear();
		EnumWindows(enumWindowCallback, NULL);
		if (PreviousVisibleWindows.size() > 0) {
			for (size_t iha = 0; iha < PreviousVisibleWindows.size(); iha++) {
				if (CurrentVisibleWindows.size() > 0) {
					bool WindowFound = false;
					for (size_t iha2 = 0; iha2 < CurrentVisibleWindows.size(); iha2++) {
						if (CurrentVisibleWindows[iha2] == PreviousVisibleWindows[iha]) {
							WindowFound = true;
							break;
						}
					}
					if (!WindowFound) {
						std::wcout << L"Window with class name is not longer shown: " << PreviousVisibleWindows[iha] << endl;
					}
				}
			}
			if (CurrentVisibleWindows.size() > 0) {
				for (size_t iha = 0; iha < CurrentVisibleWindows.size(); iha++) {
					if (PreviousVisibleWindows.size() > 0) {
						bool WindowFound = false;
						for (size_t iha2 = 0; iha2 < PreviousVisibleWindows.size(); iha2++) {
							if (PreviousVisibleWindows[iha2] == CurrentVisibleWindows[iha]) {
								WindowFound = true;
								break;
							}
						}
						if (!WindowFound) {
							std::wcout << L"New window with class name is now shown: " << CurrentVisibleWindows[iha] << endl;
						}
					}
				}
			}
		}
		PreviousVisibleWindows = CurrentVisibleWindows;

		Sleep(1000);
		continue;
		//Detect_if_Clipboard_Has_Dragged_File_Data();
		HWND ErrorIcon2 = FindWindowEx(NULL, 0, L"tooltips_class32", nullptr);

		if (IsWindowVisible(ErrorIcon2)) {
			std::wcout << ErrorIcon2 << " Error icon is visible!" << endl;
		}
		else {
			std::wcout << ErrorIcon2 << " Error icon is NOT visible!" << endl;
		}
		Sleep(1000);
	}
}

HBITMAP MakeBitMapTransparent(HBITMAP hbmSrc, COLORREF CustomBackgroundColor = NULL, COLORREF CustomTransparentColor = NULL, int CustomWidth = NULL, int CustomHeight = NULL)
{
	HDC hdcSrc, hdcDst;
	HBITMAP hbmOld, hbmNew = hbmSrc;
	BITMAP bm;
	COLORREF clrTP, clrBK;

	if ((hdcSrc = CreateCompatibleDC(NULL)) != NULL) {
		if ((hdcDst = CreateCompatibleDC(NULL)) != NULL) {
			int nRow, nCol;
			GetObject(hbmSrc, sizeof(bm), &bm);
			hbmOld = (HBITMAP)SelectObject(hdcSrc, hbmSrc);

			int bmWidth = bm.bmWidth;
			int bmHeight = bm.bmHeight;
			if (CustomWidth != NULL) {
				bmWidth = CustomWidth;
			}
			if (CustomHeight != NULL) {
				bmHeight = CustomHeight;
			}

			hbmNew = CreateBitmap(bmWidth, bmHeight, bm.bmPlanes, bm.bmBitsPixel, NULL);
			SelectObject(hdcDst, hbmNew);

			BitBlt(hdcDst, 0, 0, bmWidth, bmHeight, hdcSrc, 0, 0, SRCCOPY);

			clrTP = GetPixel(hdcDst, 0, 0);// Get color of first pixel at 0,0
			if (CustomTransparentColor != NULL) {
				clrTP = CustomTransparentColor;
			}
			clrBK = GetSysColor(COLOR_BTNFACE);// Get the current background color of the menu
			if (CustomBackgroundColor != NULL) {
				clrBK = CustomBackgroundColor;
			}

			for (nRow = 0; nRow < bm.bmHeight; nRow++)// work our way through all the pixels changing their color
				for (nCol = 0; nCol < bm.bmWidth; nCol++)// when we hit our set transparency color.
					if (GetPixel(hdcDst, nCol, nRow) == clrTP)
						SetPixel(hdcDst, nCol, nRow, clrBK);

			DeleteDC(hdcDst);
		}
		DeleteDC(hdcSrc);

	}

	return hbmNew;
}

HBITMAP TaskManagerIcon() {
	HDC Screen_Handle = GetDC(NULL);
	HDC Device_Handle = CreateCompatibleDC(Screen_Handle);

	HBITMAP Bitmap_Handle =
		CreateCompatibleBitmap(Device_Handle, GetSystemMetrics(SM_CXICON),
			GetSystemMetrics(SM_CYICON));

	HBITMAP Old_Bitmap = (HBITMAP)SelectObject(Device_Handle, Bitmap_Handle);

	/*/HINSTANCE hDll;
	hDll = LoadLibraryW(L"Taskmgr.exe");
	//HICON TaskManagerIcon = ExtractIconW((HINSTANCE)hDll, L"Taskmgr.exe", 0);
	HICON TaskManagerIcon = LoadIcon(hDll, MAKEINTRESOURCE(0)); */


		HICON hIconLarge, hIconSmall;
	ICONINFO oIconInfo;
	ExtractIconExW(L"shell32.dll", 1, &hIconLarge, &hIconSmall, 1);
	GetIconInfo(hIconSmall, &oIconInfo);
	HICON TaskManagerIcon = hIconSmall;

	if (TaskManagerIcon) {
		std::wcout << L"Not null ICON" << std::endl;
	}


	//HICON TaskManagerIcon = LoadIcon(hDll, MAKEINTRESOURCE(0));

	DrawIcon(Device_Handle, 0, 0, TaskManagerIcon);
	SelectObject(Device_Handle, Old_Bitmap);

	DeleteDC(Device_Handle);
	ReleaseDC(NULL, Screen_Handle);
	return Bitmap_Handle;
}

HBITMAP Bitmap1;
HWND TaskManagerIconWindow;
HDC MemDC;
HBITMAP hOldBmp;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	wchar_t greeting[] = L"Task Manager";

	switch (message)
	{
	case WM_CREATE:
		/*/Bitmap1 = TaskManagerIcon();
		Bitmap1 = MakeBitMapTransparent(Bitmap1);
		TaskManagerIconWindow = CreateWindowW(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_BITMAP | WS_EX_CONTROLPARENT, 5, 2, 25, 25, hWnd, (HMENU)121212, NULL, NULL);
		SendMessageW(TaskManagerIconWindow, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bitmap1);*/


		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//Bitmap:
		 // Load the bitmap from the resource
		Bitmap1 = TaskManagerIcon();
		//Bitmap1 = MakeBitMapTransparent(Bitmap1);
		// Create a memory device compatible with the above DC variable
		MemDC = CreateCompatibleDC(hdc);
		// Select the new bitmap
		hOldBmp = (HBITMAP)SelectObject(MemDC, Bitmap1);

		// Copy the bits from the memory DC into the current dc
		BitBlt(hdc, 5, 2, 32, 32, MemDC, 0, 0, SRCCOPY);

		// Restore the old bitmap
		SelectObject(MemDC, hOldBmp);
		DeleteObject(Bitmap1);


		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		TextOutW(hdc,
			20, 5,
			greeting, wcslen(greeting));
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}*/

#endif
