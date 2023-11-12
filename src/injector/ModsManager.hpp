#pragma once

#include <vector>
#include <utility>
#include "ModInfos.hpp"
#include "MonoModule.hpp"

namespace Xash
{
    namespace Injector
    {
        class ModsManager
		{
		public:
			static ModsManager &getInstance()
			{
				static ModsManager instance;
				return instance;
			}

			ModsManager(const ModsManager &) = delete;
			ModsManager(const ModsManager &&) = delete;
			ModsManager &operator=(const ModsManager &) = delete;
			ModsManager &operator=(const ModsManager &&) = delete;

            void LoadMod(const ModInfos &modInfos);
            void UnLoadMod(const ModInfos &modInfos);

            const std::vector<std::pair<ModInfos, MonoModule>> &getLoadedMods() const;

		private:
			ModsManager() = default;
			~ModsManager() = default;

            std::vector<std::pair<ModInfos, MonoModule>> mLoadedMods;
		};
    }
}
