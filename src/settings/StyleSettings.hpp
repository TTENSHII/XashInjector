#pragma once

namespace Xash
{
	struct Vector4
	{
		Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
		float x;
		float y;
		float z;
		float w;
	};

	namespace Settings
	{
		class StyleSettings
		{
		public:
			static StyleSettings &GetInstance()
			{
				static StyleSettings instance;
				return instance;
			}

			StyleSettings(const StyleSettings &) = delete;
			StyleSettings(const StyleSettings &&) = delete;
			StyleSettings &operator=(const StyleSettings &) = delete;
			StyleSettings &operator=(const StyleSettings &&) = delete;

		public:
			void SetBackgroundColor(const Vector4 &color);
			void SetTextColor(const Vector4 &color);
			void SetBorderColor(const Vector4 &color);
			void SetButtonColor(const Vector4 &color);

			const Vector4 &GetBackgroundColor() const;
			const Vector4 &GetTextColor() const;
			const Vector4 &GetBorderColor() const;
			const Vector4 &GetButtonColor() const;

		private:
			StyleSettings() = default;
			~StyleSettings() = default;

			Vector4 mBackgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
			Vector4 mTextColor = {1.0f, 1.0f, 1.0f, 1.0f};
			Vector4 mBorderColor = {0.5f, 0.5f, 0.5f, 1.0f};
			Vector4 mButtonColor = {0.2f, 0.8f, 0.2f, 1.0f};
		};
	} // namespace Settings
} // namespace Xash
