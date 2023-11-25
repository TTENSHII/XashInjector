#include <string>
#include <functional>
#include "imgui.h"
#include "Imgui.hpp"
#include "XashSettings.hpp"
#include "StyleSettings.hpp"
#include "ThemePresets.hpp"

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

		// All theme presets with associated functions
		std::unordered_map<std::string, std::function<void()>> colorPresets = {
			{"Default", Themes::SetDefaultColors},
			{"Arcade", Themes::SetArcadeColors},
			{"BlackAndWhite", Themes::SetBlackAndWhiteColors},
			{"Purple", Themes::SetPurpleColors},
			{"Ocean", Themes::SetOceanColors}
		};

		static void SetColors(const std::string &presetName)
		{
			auto &style = Settings::StyleSettings::GetInstance();

			auto preset = colorPresets.find(presetName);
			if (preset != colorPresets.end())
			{
				preset->second();
			}
		}

		static void ThemePresets(const std::function<void()>& ApplyThemePreset)
		{
			for (const auto &preset : colorPresets)
			{
				if (ImGui::Button(preset.first.c_str()))
				{
					SetColors(preset.first);
					ApplyThemePreset();
				}
				ImGui::SameLine();
			}
		}

		void Imgui::DrawSettingsPanel()
		{
			if (ImGui::CollapsingHeader("Custom Theme"))
			{
				customTheme();
			}
			if (ImGui::CollapsingHeader("Theme Presets"))
			{
				auto applyThemefunc = [this]() {ApplyThemePreset();};
            	ThemePresets(applyThemefunc);
			}
		}
	} // namespace GUI
} // namespace Xash
