#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include "System.hpp"
#include "Imgui.hpp"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace Xash::GUI
{
	Imgui::Imgui()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		GetProcessesNames();
		ApplyThemePreset();
	}

	void Imgui::InitWin32AndDX11(
		const HWND &window, Microsoft::WRL::ComPtr<ID3D11Device> device,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext
	)
	{
		if (ImGui_ImplWin32_Init(window) == false)
		{
			throw std::runtime_error("Failed to initialize ImGui Win32");
		}
		if (ImGui_ImplDX11_Init(device.Get(), deviceContext.Get()) == false)
		{
			throw std::runtime_error("Failed to initialize ImGui DX11");
		}
	}

	Imgui::~Imgui()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void Imgui::Render()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void Imgui::Draw()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		DrawSideBar();
		MaximizeMainWindow();
		ImGui::Begin(
			"Xash", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar
		);
		DrawPanels();
		ImGui::End();
	}

	void Imgui::DrawPanels()
	{
		static const std::unordered_map<ActivePanel, std::function<void()>> mPanelsDrawers = {
			{ActivePanel::INJECT, std::bind(&Imgui::DrawInjectPanel, this)},
			{ActivePanel::EJECT, std::bind(&Imgui::DrawEjectPanel, this)},
			{ActivePanel::SETTINGS, std::bind(&Imgui::DrawSettingsPanel, this)}
		};

		auto it = mPanelsDrawers.find(mActivePanel);
		if (it != mPanelsDrawers.end())
		{
			it->second();
		}
	}

	void Imgui::MaximizeMainWindow()
	{
		ImGui::SetNextWindowSize(
			ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y)
		);
		ImGui::SetNextWindowPos(mainWindowPos);
	}

	void Imgui::GetProcessesNames()
	{
		mProcessesNames = Xash::System::GetRunningProcessesNames();
		std::sort(mProcessesNames.begin(), mProcessesNames.end());
		mProcessesNames.erase(
			std::unique(mProcessesNames.begin(), mProcessesNames.end()),
			mProcessesNames.end()
		);
	}

	void Imgui::ApplyThemePreset()
	{
		auto &imguiStyle = ImGui::GetStyle();
		const auto &xashStyle = Settings::StyleSettings::GetInstance();

		imguiStyle.Colors[ImGuiCol_WindowBg] = {
			xashStyle.GetBackgroundColor().x, xashStyle.GetBackgroundColor().y,
			xashStyle.GetBackgroundColor().z, xashStyle.GetBackgroundColor().w
		};
		imguiStyle.Colors[ImGuiCol_Text] = {
			xashStyle.GetTextColor().x, xashStyle.GetTextColor().y,
			xashStyle.GetTextColor().z, xashStyle.GetTextColor().w
		};
		imguiStyle.Colors[ImGuiCol_Border] = {
			xashStyle.GetBorderColor().x, xashStyle.GetBorderColor().y,
			xashStyle.GetBorderColor().z, xashStyle.GetBorderColor().w
		};
		imguiStyle.Colors[ImGuiCol_Button] = {
			xashStyle.GetButtonColor().x, xashStyle.GetButtonColor().y,
			xashStyle.GetButtonColor().z, xashStyle.GetButtonColor().w
		};
	}
} // namespace Xash::GUI
