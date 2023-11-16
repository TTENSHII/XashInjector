#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include <utility>
#include "ModInfos.hpp"
#include "MonoModule.hpp"
#include "imgui.h"

namespace Xash
{
	namespace GUI
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
			void DrawModInfos(
				const Injector::ModInfos &modInfos,
				const std::pair<Injector::ModInfos, Injector::MonoModule> &loadedMod
			);

			// SETTINGS
			void DrawSettingsPanel();

			Injector::ModInfos mModInfos;
			std::size_t mSelectedProcessIndex = 0;
			std::vector<std::string> mProcessesNames;
			ActivePanel mActivePanel = ActivePanel::INJECT;
		};
	} // namespace GUI
} // namespace Xash
