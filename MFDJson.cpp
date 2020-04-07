#include "MFDJson.h"

#include "Include\json.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

std::vector<std::wstring> MFDJson::keys = std::vector<std::wstring>();
std::vector<std::string> MFDJson::values = std::vector<std::string>();
MFDPage* MFDJson::page = nullptr;
int MFDJson::currentIndex = 0;

void __stdcall MFDJson::DirectOutput_SoftButton_Callback(void* hDevice, DWORD dwButtons, void* pvContext)
{
	switch (dwButtons)
	{
	case SoftButton_Up:
		currentIndex--;
		if (currentIndex < 0)
			currentIndex = keys.size() - 1;
		break;

	case SoftButton_Down:
		currentIndex++;
		currentIndex %= keys.size();
		break;

	case SoftButton_Select:
		std::string string = values[currentIndex];

		std::cout << "Sending " << string << std::endl;
		
		string = ReplaceString(string, "shift", ToHexString(VK_SHIFT));
		string = ReplaceString(string, "ctrl", ToHexString(VK_CONTROL));
		string = ReplaceString(string, "alt", ToHexString(VK_MENU));

		std::vector<INPUT> pressedKeys;
		std::stringstream strStream;
		auto strIt = string.begin();

		while (strIt <= string.end())
		{
			bool atEnd = strIt == string.end();
			if (atEnd || *strIt == ';')
			{
				std::string value = strStream.str();
				if (value.length() > 0)
				{
					strStream = std::stringstream();

					SHORT keycode = 0;
					if (value.size() > 2 && value[0] == '0' && value[1] == 'x')
						keycode = std::stoul(value, nullptr, 16);
					else
					{
						char key = value[0];
						keycode = VkKeyScanEx(key, GetKeyboardLayout(0));
					}

					INPUT input;
					input.type = INPUT_KEYBOARD;
					input.ki.wScan = MapVirtualKeyA(keycode, MAPVK_VK_TO_VSC);
					input.ki.time = 0;
					input.ki.dwExtraInfo = 0;
					input.ki.wVk = 0;
					input.ki.dwFlags = KEYEVENTF_SCANCODE;

					SendInput(1, &input, sizeof(INPUT));
					pressedKeys.push_back(input);
				}
			}
			else
				strStream << *strIt;

			if (!atEnd)
				strIt++;
			else
				break;
		}

		Sleep(20);
		for (INPUT input : pressedKeys)
		{
			input.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
			SendInput(1, &input, sizeof(INPUT));
		}
		break;
	}
	
	UpdateStrings();
}

std::wstring MFDJson::SelectText(std::wstring string)
{
	return std::wstring(L"<").append(string).append(L">");
}

std::string MFDJson::ReplaceString(std::string string, std::string from, std::string to)
{
	int start = string.find(from);
	if (start >= 0)
		string = string.erase(start, from.length()).insert(start, to);
	return string;
}

template<typename T>
std::string MFDJson::ToHexString(T value)
{
	std::stringstream stream;
	stream << "0x" << std::hex << value;
	return stream.str();
}

void MFDJson::InitialiseMap(const char* filePath)
{
	std::ifstream fileStream = std::ifstream(filePath);
	if (!fileStream.is_open())
		throw std::exception("Map file not found");

	nlohmann::basic_json<std::map> jMap;
	fileStream >> jMap;
	fileStream.close();

	for (auto it = jMap.begin(); it != jMap.end(); it++)
	{
		const size_t keySize = it.key().size() + 1;
		std::wstring key(keySize, L'#');
		mbstowcs_s(nullptr, &key[0], keySize, it.key().c_str(), keySize);
		key.resize(keySize - 1);
		keys.push_back(key);
		values.push_back(it.value());
	}

	if (page == nullptr)
		page = MFD::AddPage(true);

	MFD::RegisterButtonCallback(*DirectOutput_SoftButton_Callback);
	UpdateStrings();
}

void MFDJson::ClearMap()
{
	keys.clear();
	values.clear();
}

void MFDJson::UpdateStrings()
{
	if (page == nullptr)
		return;
	int keyCount = keys.size();
	if (keyCount > 3)
	{
		int last = currentIndex - 1;
		int next = ((size_t)currentIndex + 1) % keyCount;
		if (last < 0)
			last = keyCount - 1;

		page->SetStrings(keys[last], SelectText(keys[currentIndex]), keys[next]);
	}
	else
	{
		std::vector<std::wstring> strings = keys;
		while (strings.size() < 3)
			strings.push_back(L"");
		strings[currentIndex] = SelectText(strings[currentIndex]);
		page->SetStrings(strings[0], strings[1], strings[2]);
	}
	MFD::UpdateStrings(page);
}
