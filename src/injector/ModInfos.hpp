#pragma once

#include <string>

namespace Xash::Injector
{
	struct ModInfos
	{
		std::string modPath;
		std::string modNamespace;
		std::string modClass;
		std::string modInitMethod;
		std::string modUnloadMethod;
		std::string targetedProcessName;

		bool operator==(const ModInfos &other) const
		{
			if (modPath != other.modPath ||
				modNamespace != other.modNamespace ||
				modClass != other.modClass) {
				return false;
			}
			return true;
		}
	};
} // namespace Xash::Injector
