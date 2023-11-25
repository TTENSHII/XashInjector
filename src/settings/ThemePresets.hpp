#pragma once

#include "StyleSettings.hpp"

// Maybe soon, themes will be in a json file

namespace Xash::Themes
{
	void SetArcadeColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.09f, 0.05f, 0.201f, 1.0f});
		style.SetTextColor({1.0f, 1.0f, 1.0f, 1.0f});
		style.SetBorderColor({1.0f, 0.0f, 1.0f, 1.0f});
		style.SetButtonColor({0.05f, 0.860f, 0.780f, 1.0f});
	}

	void SetBlackAndWhiteColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.076f, 0.076f, 0.076f, 1.0f});
		style.SetTextColor({0.8f, 0.8f, 0.8f, 1.0f});
		style.SetBorderColor({0.5f, 0.5f, 0.5f, 1.0f});
		style.SetButtonColor({0.3f, 0.3f, 0.3f, 1.0f});
	}

	void SetPurpleColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.185f, 0.138f, 0.310f, 1.0f});
		style.SetTextColor({1.0f, 1.0f, 1.0f, 1.0f});
		style.SetBorderColor({0.279f, 0.189f, 0.359f, 1.0f});
		style.SetButtonColor({0.322f, 0.148f, 0.620f, 1.0f});
	}

	void SetOceanColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.0f, 0.2f, 0.4f, 1.0f});
		style.SetTextColor({1.0f, 1.0f, 1.0f, 1.0f});
		style.SetBorderColor({0.3f, 0.5f, 0.7f, 1.0f});
		style.SetButtonColor({0.2f, 0.5f, 0.8f, 1.0f});
	}

	void SetDefaultColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.088f, 0.084f, 0.098f, 1.0f});
		style.SetTextColor({1.0f, 1.0f, 1.0f, 1.0f});
		style.SetBorderColor({0.538f, 0.538f, 0.538f, 1.0f});
		style.SetButtonColor({0.321f, 0.112f, 0.734f, 1.0f});
	}
} // namespace Themes
