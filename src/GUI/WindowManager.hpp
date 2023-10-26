#pragma once

#include <windows.h>
#include "DirectX11.hpp"
#include "Imgui.hpp"

namespace Xash
{
	namespace GUI
	{
		class WindowManager
		{
			static constexpr LPCWSTR WindowName = L"Xash";
			static constexpr UINT WindowWidth = 700;
			static constexpr UINT WindowHeight = 400;
			static constexpr LPCWSTR IconPath = L"assets\\icon.ico";

		public:
			WindowManager(HINSTANCE hInstance);
			~WindowManager();

			bool IsRunning() const;
			void Update();
			void Display();

		private:
			bool InitWindow();
			void CreateWindowClass();
			void InitIcon();
			void ApplyDarkMode();
			void HandleWindowMessages();

			static LRESULT CALLBACK
			WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			HWND hWindow = nullptr;
			HICON hIcon = nullptr;
			HINSTANCE hInstance = nullptr;
			WNDCLASSEXW mWindowClass = {0};

			DirectX11 mDx11;
			Imgui mImgui;

			BOOL bIsDarkMode = TRUE;
			bool bIsRunning = true;
			bool bIsWindowClassRegistered = false;
		};
	} // namespace GUI
} // namespace Xash
