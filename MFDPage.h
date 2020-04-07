#ifndef _H_MFDPAGE_
#define _H_MFDPAGE_

#include <string>
#include <Windows.h>

class MFDPage
{
	std::wstring topString;
	std::wstring midString;
	std::wstring botString;

	DWORD page;

public:

	MFDPage(DWORD page);

	void SetTopString(const wchar_t* string);
	void SetTopString(std::wstring string);
	const wchar_t* GetTopString();
	DWORD GetTopLength();
	void SetMiddleString(const wchar_t* string);
	void SetMiddleString(std::wstring string);
	const wchar_t* GetMiddleString();
	DWORD GetMiddleLength();
	void SetBottomString(const wchar_t* string);
	void SetBottomString(std::wstring string);
	const wchar_t* GetBottomString();
	DWORD GetBottomLength();
	void SetStrings(const wchar_t* top, const wchar_t* middle, const wchar_t* bottom);
	void SetStrings(std::wstring top, std::wstring middle, std::wstring bottom);

	DWORD GetPage();
};

#endif //_H_MFDPAGE_