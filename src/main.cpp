#include <windows.h>
#include <iostream>

int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    #ifndef NDEBUG
	    std::wcout << L"Debug mode" << std::endl;
    #else
        std::wcout << L"Release mode" << std::endl;
    #endif
	return 0;
}
