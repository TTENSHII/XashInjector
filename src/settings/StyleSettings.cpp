#include "StyleSettings.hpp"

namespace Xash
{
	Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	namespace Settings
	{
        // Setters

		void StyleSettings::SetBackgroundColor(const Vector4 &color)
        {
            mBackgroundColor = color;
        }

        void StyleSettings::SetTextColor(const Vector4 &color)
        {
            mTextColor = color;
        }

        void StyleSettings::SetBorderColor(const Vector4 &color)
        {
            mBorderColor = color;
        }

        void StyleSettings::SetButtonColor(const Vector4 &color)
        {
            mButtonColor = color;
        }

        // Getters

        const Vector4 &StyleSettings::GetBackgroundColor() const
        {
            return mBackgroundColor;
        }

        const Vector4 &StyleSettings::GetTextColor() const
        {
            return mTextColor;
        }

        const Vector4 &StyleSettings::GetBorderColor() const
        {
            return mBorderColor;
        }

        const Vector4 &StyleSettings::GetButtonColor() const
        {
            return mButtonColor;
        }
        
	} // namespace Settings
} // namespace Xash
