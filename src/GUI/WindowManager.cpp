#include <stdexcept>
#include <dwmapi.h>
#include <iostream>
#include "WindowManager.hpp"
#include "backends/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT
ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Xash::GUI
{
	WindowManager::WindowManager(HINSTANCE instance) : hInstance(instance)
	{
		try
		{
			InitIcon();
			CreateWindowClass();
			InitWindow();
			mDx11.Init(hWindow);
			mImgui.InitWin32AndDX11(hWindow, mDx11.GetDevice(), mDx11.GetDeviceContext());
			ApplyDarkMode();
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			bIsRunning = false;
		}
	}

	WindowManager::~WindowManager()
	{
		if (hIcon)
		{
			DestroyIcon(hIcon);
		}
		if (hWindow)
		{
			DestroyWindow(hWindow);
		}
		if (bIsWindowClassRegistered)
		{
			UnregisterClassW(mWindowClass.lpszClassName, mWindowClass.hInstance);
		}
	}

	// PUBLIC METHODS

	bool WindowManager::IsRunning() const
	{
		return bIsRunning;
	}

	void WindowManager::Display()
	{
		mDx11.Display();
	}

	void WindowManager::Update()
	{
		HandleWindowMessages();
		mDx11.Clear();
		mImgui.Draw();
		mImgui.Render();
	}

	// PRIVATE METHODS

	void WindowManager::HandleWindowMessages()
	{
		MSG message = {0};
		constexpr UINT msgFilterMin = 0;
		constexpr UINT msgFilterMax = 0;

		while (PeekMessageW(&message, nullptr, msgFilterMin, msgFilterMax, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
			if (message.message == WM_QUIT)
			{
				bIsRunning = FALSE;
				break;
			}
		}
	}

	LRESULT CALLBACK
	WindowManager::WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		{
			return true;
		}
		if (uMsg == WM_DESTROY)
		{
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}

	// INITIALIZATION METHODS

	bool WindowManager::InitWindow()
	{
		hWindow = CreateWindowExW(
			WS_EX_ACCEPTFILES, mWindowClass.lpszClassName, WindowName,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
			WindowWidth, WindowHeight, nullptr, nullptr, mWindowClass.hInstance, nullptr
		);
		if (!hWindow)
		{
			throw std::runtime_error("Failed to create window");
		}
		ShowWindow(hWindow, SW_SHOWDEFAULT);
		return true;
	}

	void WindowManager::InitIcon()
	{
		constexpr int iconSize = 0;

		hIcon = (HICON)LoadImageW(
			hInstance, IconPath, IMAGE_ICON, iconSize, iconSize,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		);
		if (!hIcon)
		{
			throw std::runtime_error("Failed to load icon");
		}
	}

	void WindowManager::ApplyDarkMode()
	{
		DwmSetWindowAttribute(
			hWindow, DWMWINDOWATTRIBUTE::DWMWA_USE_IMMERSIVE_DARK_MODE, &bIsDarkMode,
			sizeof(bIsDarkMode)
		);
	}

	void WindowManager::CreateWindowClass()
	{
		constexpr UINT windowClassStyle = 0;

		mWindowClass.cbSize = sizeof(WNDCLASSEXW);
		mWindowClass.style = windowClassStyle;
		mWindowClass.lpfnWndProc = WindowProcedure;
		mWindowClass.hInstance = hInstance;
		mWindowClass.hIcon = hIcon;
		mWindowClass.hIconSm = hIcon;
		mWindowClass.lpszClassName = WindowName;
		if (!RegisterClassExW(&mWindowClass))
		{
			throw std::runtime_error("Failed to register window class");
		}
		bIsWindowClassRegistered = true;
	}

} // namespace Xash::GUI
