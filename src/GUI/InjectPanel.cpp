#include "imgui.h"
#include "Imgui.hpp"
#include "System.hpp"
#include "ModsManager.hpp"

namespace Xash::GUI
{

	void Imgui::DrawInjectButton()
	{
		if (ImGui::Button("Inject"))
		{
			Xash::Injector::ModsManager &modsManager = Xash::Injector::ModsManager::getInstance();
			mModInfos.targetedProcessName = mProcessesNames[mSelectedProcessIndex];
			modsManager.LoadMod(mModInfos);
		}
	}

	void Imgui::DrawProcessesBox()
	{
		if (ImGui::BeginCombo("##combo", mProcessesNames[mSelectedProcessIndex].c_str()))
		{
			for (int i = 0; i < mProcessesNames.size(); i++)
			{
				bool isSelected = (mSelectedProcessIndex == i);
				if (ImGui::Selectable(mProcessesNames[i].c_str(), isSelected))
				{
					mSelectedProcessIndex = i;
				}  
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}

	void Imgui::DrawDllBox()
	{
		static std::string selectedFile = "Select mod DLL";

		if (ImGui::Selectable(selectedFile.c_str()))
		{
			OPENFILENAME ofn;
			TCHAR filePath[MAX_PATH] = {0};
			TCHAR currentDir[MAX_PATH] = {0};
			GetCurrentDirectory(MAX_PATH, currentDir);

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFilter = "DLL\0*.dll\0";
			ofn.lpstrFile = filePath;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrTitle = "Select DLL";
			ofn.Flags = OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&ofn))
			{
				SetCurrentDirectory(currentDir);
				selectedFile = ofn.lpstrFile;
				mModInfos.modPath = selectedFile;
			}
		}
	}

	void Imgui::DrawInjectInputs()
	{
		char namespaceBuffer[256] = {0};
		char classNameBuffer[256] = {0};
		char loadMethodNameBuffer[256] = {0};

		strcpy_s(namespaceBuffer, mModInfos.modNamespace.c_str());
		strcpy_s(classNameBuffer, mModInfos.modClass.c_str());
		strcpy_s(loadMethodNameBuffer, mModInfos.modInitMethod.c_str());

		ImGui::InputText("Namespace", namespaceBuffer, IM_ARRAYSIZE(namespaceBuffer));
		ImGui::InputText("Class", classNameBuffer, IM_ARRAYSIZE(classNameBuffer));
		ImGui::InputText(
			"Load Method", loadMethodNameBuffer, IM_ARRAYSIZE(loadMethodNameBuffer)
		);

		mModInfos.modNamespace = namespaceBuffer;
		mModInfos.modClass = classNameBuffer;
		mModInfos.modInitMethod = loadMethodNameBuffer;
	}

	void Imgui::DrawInjectPanel()
	{
		DrawProcessesBox();
		DrawDllBox();
		DrawInjectInputs();
		DrawInjectButton();
	}
} // namespace Xash::GUI
