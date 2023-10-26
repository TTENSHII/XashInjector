#include <windows.h>
#include <iostream>
#include "WindowManager.hpp"

int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	Xash::GUI::WindowManager windowManager(hInstance);
	while (windowManager.IsRunning())
	{
		windowManager.Update();
		windowManager.Display();
	}
	return 0;
}
