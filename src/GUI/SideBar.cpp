#include <unordered_map>
#include "Imgui.hpp"
#include "imgui.h"

static void addSideBarStyle()
{
	ImVec4 transparent = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	ImVec4 hoverColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	ImVec4 selectedColor = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);

	ImGui::PushStyleColor(ImGuiCol_Button, transparent);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, selectedColor);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.0f, 0.5f));
}

static void removeSideBarStyle()
{
	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar(2);
}

static void createSideBarWindow()
{
	ImGui::Begin("##sidebar", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowSize(ImVec2(120, ImGui::GetIO().DisplaySize.y));
	ImGui::SetWindowPos(ImVec2(0, 0));
}

void Xash::GUI::Imgui::DrawSideBar()
{
	static std::unordered_map<ActivePanel, std::string> panelNames = {
        { ActivePanel::INJECT, "Inject" },
        { ActivePanel::EJECT, "Loaded Dll" },
        { ActivePanel::CONFIG, "Config" },
        { ActivePanel::SETTINGS, "Settings" }
    };

	createSideBarWindow();
	addSideBarStyle();

	for (auto &panel : panelNames)
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
		ImGui::SetCursorPosX(10);

		if (ImGui::Button(panel.second.c_str(), ImVec2(200, 25)))
		{
			mActivePanel = panel.first;
		}
	}

	removeSideBarStyle();
	ImGui::End();
}
