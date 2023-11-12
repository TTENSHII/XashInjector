#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include "ModInfos.hpp"
#include "imgui.h"

namespace Xash::GUI
{
	class Imgui
	{
		static constexpr ImVec2 mainWindowPos = ImVec2(120, 0);

	public:
		Imgui();
		~Imgui();

		void InitWin32AndDX11(
			const HWND &window, Microsoft::WRL::ComPtr<ID3D11Device> device,
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext
		);
		void Draw();
		void Render();

	private:
		enum class ActivePanel : uint8_t
		{
			INJECT,
			EJECT,
			CONFIG,
			SETTINGS
		};

		void DrawSideBar();
		void DrawPanels();
		void MaximizeMainWindow();

		// INJECT
		void DrawInjectPanel();
		void DrawProcessesBox();
		void DrawDllBox();
		void DrawInjectInputs();
		void DrawInjectButton();
		void GetProcessesNames();

		// EJECT
		void DrawEjectPanel();

		// CONFIG
		void DrawConfigPanel();

		// SETTINGS
		void DrawSettingsPanel();

		Injector::ModInfos mModInfos;
		std::size_t mSelectedProcessIndex = 0;
		std::vector<std::string> mProcessesNames;
		ActivePanel mActivePanel = ActivePanel::INJECT;
	};
} // namespace Xash::GUI
