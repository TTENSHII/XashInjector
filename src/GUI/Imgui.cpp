#include <stdexcept>
#include "imgui.h"
#include "Imgui.hpp"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace Xash::GUI
{
	Imgui::Imgui()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
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

		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin(
			"Main Window", nullptr,
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar
		);
		ImGui::Text("Xash Injector");

		ImGui::End();
	}
} // namespace Xash::GUI
