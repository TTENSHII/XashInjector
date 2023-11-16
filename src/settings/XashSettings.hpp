#pragma once

namespace Xash
{
	namespace Settings
	{
		class XashSettings
		{
		public:
			static XashSettings &GetInstance()
			{
				static XashSettings instance;
				return instance;
			}

			XashSettings(const XashSettings &) = delete;
			XashSettings(const XashSettings &&) = delete;
			XashSettings &operator=(const XashSettings &) = delete;
			XashSettings &operator=(const XashSettings &&) = delete;

		private:
			XashSettings() = default;
			~XashSettings() = default;
		};
	} // namespace Settings
} // namespace Xash
