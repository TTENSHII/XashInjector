#include <string>
#include "imgui.h"
#include "Imgui.hpp"
#include "XashSettings.hpp"
#include "StyleSettings.hpp"

namespace Xash
{
	namespace GUI
	{
		static void customTheme()
		{
			constexpr std::string_view backgroundLabel = "Background Color";
			constexpr std::string_view textLabel = "Text Color";
			constexpr std::string_view borderLabel = "Border Color";
			constexpr std::string_view buttonLabel = "Button Color";
			auto &style = Settings::StyleSettings::GetInstance();

			Imgui::CustomColorPicker(
				backgroundLabel,
				[&style]() -> const Vector4 & { return style.GetBackgroundColor(); },
				[&style](const Vector4 &color) { style.SetBackgroundColor(color); },
				ImGuiCol_WindowBg
			);
			Imgui::CustomColorPicker(
				textLabel, [&style]() -> const Vector4 & { return style.GetTextColor(); },
				[&style](const Vector4 &color) { style.SetTextColor(color); },
				ImGuiCol_Text
			);
			Imgui::CustomColorPicker(
				borderLabel,
				[&style]() -> const Vector4 & { return style.GetBorderColor(); },
				[&style](const Vector4 &color) { style.SetBorderColor(color); },
				ImGuiCol_Border
			);
			Imgui::CustomColorPicker(
				buttonLabel,
				[&style]() -> const Vector4 & { return style.GetButtonColor(); },
				[&style](const Vector4 &color) { style.SetButtonColor(color); },
				ImGuiCol_Button
			);
		}

		void Imgui::DrawSettingsPanel()
		{
			if (ImGui::CollapsingHeader("Custom Theme"))
			{
				customTheme();
			}
		}
	} // namespace GUI
} // namespace Xash
