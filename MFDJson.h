#ifndef _H_MFDJSON_
#define _H_MFDJSON_

#include "Output.h"

#include <vector>
#include <string>

class MFDJson
{
	static std::vector<std::wstring> keys;
	static std::vector<std::string> values;
	static MFDPage* page;
	static int currentIndex;

	static void __stdcall DirectOutput_SoftButton_Callback(void* hDevice, DWORD dwButtons, void* pvContext);

	static std::wstring SelectText(std::wstring string);

	static std::string ReplaceString(std::string string, std::string from, std::string to);
	template<typename T>
	static std::string ToHexString(T value);

public:

	static void InitialiseMap(const char* filePath);
	static void ClearMap();
	static void UpdateStrings();
};

#endif _H_MFDJSON_