#include "imgui.h"
#include "Imgui.hpp"
#include "System.hpp"
#include "ModsManager.hpp"

namespace Xash::GUI
{
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

        for (auto &loadedMod : loadedMods)
        {
            ImGui::Text("--------------------");
            ImGui::Text("Mod name: %s", loadedMod.first.modClass.c_str());
            ImGui::Text("Mod Namespace: %s", loadedMod.first.modNamespace.c_str());
            ImGui::Text("Mod Path: %s", loadedMod.first.modPath.c_str());
            ImGui::Text("Targeted process: %s", loadedMod.first.targetedProcessName.c_str());
            if (ImGui::Button("Eject"))
            {
                Injector::ModInfos modInfos = loadedMod.first;
                modInfos.modUnloadMethod = mModInfos.modUnloadMethod;
                modsManager.UnLoadMod(modInfos);
            }
        }
	}
}
