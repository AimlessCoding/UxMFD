#ifndef _H_OUTPUT_
#define _H_OUTPUT_

extern "C" {
#include "Include\DirectOutput.h"
}
#include "MFDPage.h"

#include <vector>
#include <exception>
#include <string>

class MFD
{
	static std::vector<void*> g_devices;
	static std::vector<MFDPage*> g_pages;

	static void __stdcall DirectOutput_Device_Callback(void* hDevice, bool bAdded, void* pvContext);
	static void __stdcall DirectOutput_Enumerate_Callback(void* hDevice, void* pvContext);
	static void __stdcall DirectOutput_Page_Callback(void* hDevice, DWORD dwPage, bool bActivated, void* pvContext);

	class DeviceNotAddedException : std::exception {};

public:
	static void Initialise(const wchar_t* name);
	static void End();
	static void UpdateStrings();
	static void UpdateStrings(MFDPage* page);
	static MFDPage *AddPage(bool setActive = false);

	static void RegisterButtonCallback(Pfn_DirectOutput_SoftButtonChange callback);


	static const DWORD LED_FIRE = 0;
	static const DWORD LED_FIRE_A_RED = 1;
	static const DWORD LED_FIRE_A_GREEN = 2;
	static const DWORD LED_FIRE_B_RED = 3;
	static const DWORD LED_FIRE_B_GREEN = 4;
	static const DWORD LED_FIRE_D_RED = 5;
	static const DWORD LED_FIRE_D_GREEN = 6;
	static const DWORD LED_FIRE_E_RED = 7;
	static const DWORD LED_FIRE_E_GREEN = 8;
	static const DWORD LED_TOGGLE_1_2_RED = 9;
	static const DWORD LED_TOGGLE_1_2_GREEN = 10;
	static const DWORD LED_TOGGLE_3_4_RED = 11;
	static const DWORD LED_TOGGLE_3_4_GREEN = 12;
	static const DWORD LED_TOGGLE_5_6_RED = 13;
	static const DWORD LED_TOGGLE_5_6_GREEN = 14;
	static const DWORD LED_POV_2_RED = 15;
	static const DWORD LED_POV_2_GREEN = 16;
	static const DWORD LED_CLUTCH_RED = 17;
	static const DWORD LED_CLUTCH_GREEN = 18;
	static const DWORD LED_THROTTLE = 19;

	static const DWORD MFD_STRING_TOP = 0;
	static const DWORD MFD_STRING_MIDDLE = 1;
	static const DWORD MFD_STRING_BOTTOM = 2;
};

#endif //_H_OUTPUT_