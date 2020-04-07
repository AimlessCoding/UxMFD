#include "MFDPage.h"

MFDPage::MFDPage(DWORD page)
	: page(page)
{
	topString = L"";
	midString = L"";
	botString = L"";
}

void MFDPage::SetTopString(const wchar_t* string)
{
	topString = string;
}

void MFDPage::SetTopString(std::wstring string)
{
	topString = string;
}

const wchar_t* MFDPage::GetTopString()
{
	return topString.data();
}

DWORD MFDPage::GetTopLength()
{
	return topString.size();
}

void MFDPage::SetMiddleString(const wchar_t* string)
{
	midString = string;
}

void MFDPage::SetMiddleString(std::wstring string)
{
	midString = string;
}

const wchar_t* MFDPage::GetMiddleString()
{
	return midString.data();
}

DWORD MFDPage::GetMiddleLength()
{
	return midString.size();
}

void MFDPage::SetBottomString(const wchar_t* string)
{
	botString = string;
}

void MFDPage::SetBottomString(std::wstring string)
{
	botString = string;
}

const wchar_t* MFDPage::GetBottomString()
{
	return botString.data();
}

DWORD MFDPage::GetBottomLength()
{
	return botString.size();
}

void MFDPage::SetStrings(const wchar_t* top, const wchar_t* middle, const wchar_t* bottom)
{
	topString = top;
	midString = middle;
	botString = bottom;
}

void MFDPage::SetStrings(std::wstring top, std::wstring middle, std::wstring bottom)
{
	topString = top;
	midString = middle;
	botString = bottom;
}

DWORD MFDPage::GetPage()
{
	return page;
}
