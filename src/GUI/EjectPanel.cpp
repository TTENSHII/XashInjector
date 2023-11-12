#include "imgui.h"
#include "Imgui.hpp"
#include "System.hpp"
#include "ModsManager.hpp"

namespace Xash::GUI
{
    void Imgui::DrawModInfos(const Injector::ModInfos &loadedModInfos,
        const std::pair<Injector::ModInfos, Injector::MonoModule> &loadedMod)
    {
        Injector::ModsManager &modsManager = Injector::ModsManager::getInstance();

        ImGui::Text("Mod name: %s", loadedModInfos.modClass.c_str());
        ImGui::Text("Mod Namespace: %s", loadedModInfos.modNamespace.c_str());
        ImGui::Text("Mod Path: %s", loadedModInfos.modPath.c_str());
        ImGui::Text("Targeted process: %s", loadedModInfos.targetedProcessName.c_str());
		if (ImGui::Button("Eject"))
		{
			Injector::ModInfos newModInfos = loadedMod.first;
			newModInfos.modUnloadMethod = mModInfos.modUnloadMethod;
			modsManager.UnLoadMod(newModInfos);
		}
	}

	void Imgui::DrawEjectPanel()
    {
        Injector::ModsManager &modsManager = Injector::ModsManager::getInstance();
        auto &loadedMods = modsManager.getLoadedMods();

        if (loadedMods.empty())
        {
            ImGui::Text("No mod loaded");
            return;
        }

        char unloadMethodNameBuffer[256] = {0};
        strcpy_s(unloadMethodNameBuffer, mModInfos.modUnloadMethod.c_str());
        ImGui::InputText("Unload method", unloadMethodNameBuffer, sizeof(unloadMethodNameBuffer));
        mModInfos.modUnloadMethod = unloadMethodNameBuffer;
        ImGui::Separator();

        for (auto &loadedMod : loadedMods)
        {
            DrawModInfos(loadedMod.first, loadedMod);
            ImGui::Separator();
        }
	}
}
