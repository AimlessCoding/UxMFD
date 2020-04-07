#include "Output.h"

std::vector<void*> MFD::g_devices = std::vector<void*>();
std::vector<MFDPage*> MFD::g_pages = std::vector<MFDPage*>();

void __stdcall MFD::DirectOutput_Device_Callback(void* hDevice, bool bAdded, void* pvContext)
{
	if (bAdded)
		g_devices.push_back(hDevice);
	else
	{
		for (auto i = g_devices.begin(); i < g_devices.end(); i++)
		{
			if (*i == hDevice)
			{
				g_devices.erase(i);
				break;
			}
		}
	}
}

void __stdcall MFD::DirectOutput_Enumerate_Callback(void* hDevice, void* pvContext)
{
	g_devices.push_back(hDevice);
}

void __stdcall MFD::DirectOutput_Page_Callback(void* hDevice, DWORD dwPage, bool bActivated, void* pvContext)
{
	for (int i = 0; i < g_pages.size(); i++)
	{
		if (g_pages[i]->GetPage() == dwPage)
		{
			UpdateStrings(g_pages[i]);
			break;
		}
	}
}

void MFD::UpdateStrings()
{
	for (int i = 0; i < g_pages.size(); i++)
		UpdateStrings(g_pages[i]);
}

void MFD::UpdateStrings(MFDPage* page)
{
	if (!g_devices.size())
		throw DeviceNotAddedException();
	DirectOutput_SetString(g_devices[0], page->GetPage(), MFD_STRING_TOP, page->GetTopLength(), page->GetTopString());
	DirectOutput_SetString(g_devices[0], page->GetPage(), MFD_STRING_MIDDLE, page->GetMiddleLength(), page->GetMiddleString());
	DirectOutput_SetString(g_devices[0], page->GetPage(), MFD_STRING_BOTTOM, page->GetBottomLength(), page->GetBottomString());
}

void MFD::Initialise(const wchar_t* name)
{
	DirectOutput_Initialize(name);

	DirectOutput_RegisterDeviceCallback(*DirectOutput_Device_Callback, nullptr);
	DirectOutput_Enumerate(*DirectOutput_Enumerate_Callback, nullptr);

	if (!g_devices.size())
		throw DeviceNotAddedException();
	DirectOutput_RegisterPageCallback(g_devices[0], *DirectOutput_Page_Callback, nullptr);
}

void MFD::End()
{
	g_devices.clear();
	for (MFDPage* page : g_pages)
		delete page;
	g_pages.clear();
	DirectOutput_Deinitialize();
}

MFDPage *MFD::AddPage(bool setActive)
{
	if (!g_devices.size())
		throw DeviceNotAddedException();

	DWORD page = g_pages.size() + 1;
	DirectOutput_AddPage(g_devices[0], page, L"UxMFD_Page", setActive ? FLAG_SET_AS_ACTIVE : 0);

	MFDPage* mfdPage = new MFDPage(page);
	g_pages.push_back(mfdPage);
	return mfdPage;
}

void MFD::RegisterButtonCallback(Pfn_DirectOutput_SoftButtonChange callback)
{
	if (!g_devices.size())
		throw DeviceNotAddedException();

	DirectOutput_RegisterSoftButtonCallback(g_devices[0], callback, nullptr);
}
