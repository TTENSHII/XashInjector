#include <Windows.h>
#include "ModsManager.hpp"
#include "System.hpp"

namespace Xash::Injector
{
    void ModsManager::LoadMod(const ModInfos &modInfos)
    {
        for (auto &loadedMod : mLoadedMods) {
            if (loadedMod.first == modInfos) {
                MessageBoxA(nullptr, "Mod already loaded", "Error", MB_OK | MB_ICONERROR);
                return;
            }
        }
        HANDLE hProcess = Xash::System::GetProcessHandleByName(modInfos.targetedProcessName);
        mLoadedMods.emplace_back(modInfos, MonoModule(hProcess, modInfos));
        mLoadedMods.back().second.LoadMod();
    }

    void ModsManager::UnLoadMod(const ModInfos &modInfos)
    {
		auto it = mLoadedMods.begin();

		while (it != mLoadedMods.end())
		{
			if (it->first == modInfos)
			{
				it->second.UnLoadMod(modInfos.modUnloadMethod);
				it = mLoadedMods.erase(it);
				return;
			}
			else
			{
				++it;
			}
		}
		MessageBoxA(nullptr, "Mod not loaded", "Error", MB_OK | MB_ICONERROR);
    }

    const std::vector<std::pair<ModInfos, MonoModule>> &ModsManager::getLoadedMods() const
    {
        return mLoadedMods;
    }
} // namespace Xash::Injector
