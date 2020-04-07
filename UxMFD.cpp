#include <iostream>

#include "MFDJson.h"

int main()
{
	std::cout << "Initialising DirectOutput" << std::endl;
	MFD::Initialise(L"UxMFD");

	MFDJson::InitialiseMap("map.json");
	MFD::UpdateStrings();

	std::cout << "Press Enter to exit" << std::endl;
	std::cin.get();
	MFDJson::ClearMap();
	MFD::End();
	return 0;
}