#include "Imgui.hpp"
#include "imgui.h"

namespace Xash
{
	namespace GUI
	{
		static bool colorLabelClickable(const std::string_view label, const ImVec4 &color)
		{
			bool isClicked = false;

			ImGui::ColorButton("##ColorPreview", color, ImGuiColorEditFlags_NoPicker);
			if (ImGui::IsItemClicked())
			{
				isClicked = true;
			}
			ImGui::SameLine();
			ImGui::Text("%s", label.data());
			if (ImGui::IsItemClicked())
			{
				isClicked = true;
			}
			return isClicked;
		}

		static bool drawPopup(const std::string_view label, ImVec4 &color)
		{
			if (ImGui::BeginPopup(label.data()))
			{
				ImGui::ColorPicker4(
					"##ColorPicker", (float *)&color,
					ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoInputs
						| ImGuiColorEditFlags_NoSidePreview
				);
				// Slider for each color component
				ImGui::SliderFloat("##Red", &color.x, 0.0f, 1.0f, "R: %.3f");
				ImGui::SliderFloat("##Green", &color.y, 0.0f, 1.0f, "G: %.3f");
				ImGui::SliderFloat("##Blue", &color.z, 0.0f, 1.0f, "B: %.3f");
				ImGui::SliderFloat("##Alpha", &color.w, 0.0f, 1.0f, "A: %.3f");
				return true;
			}
			return false;
		}

		void Imgui::CustomColorPicker(
			const std::string_view label, std::function<Vector4()> getter,
			std::function<void(const Vector4 &)> setter, ImGuiCol_ colorIndex
		)
		{
			const auto &settingColor = getter();
			ImVec4 color{settingColor.x, settingColor.y, settingColor.z, settingColor.w};
			bool isClicked = colorLabelClickable(label, color);

			if (isClicked)
			{
				ImGui::OpenPopup(label.data());
			}
			if (drawPopup(label, color))
			{
				ImGui::GetStyle().Colors[colorIndex] =
					ImVec4(color.x, color.y, color.z, color.w);
				setter({color.x, color.y, color.z, color.w});
				ImGui::EndPopup();
			}
		}
	} // namespace GUI
} // namespace Xash
