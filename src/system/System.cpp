#include <stdexcept>
#include "System.hpp"

HMODULE Xash::System::GetModuleByKeyword(HANDLE hProcess, const std::wstring &keyword)
{
	DWORD lpcbNeeded;
	HMODULE hMods[1024];
	std::wstring modName;

	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &lpcbNeeded))
	{
		for (int i = 0; i < (lpcbNeeded / sizeof(HMODULE)); i++)
		{
			WCHAR szModName[MAX_PATH];
			if (GetModuleFileNameExW(
					hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(WCHAR)
				))
			{
				modName = szModName;
				if (modName.find(keyword) != std::string::npos)
				{
					return hMods[i];
				}
			}
		}
	}
	return nullptr;
}

DWORD Xash::System::GetProcessIdByName(const std::wstring &processName)
{
	DWORD processId = 0;
	PROCESSENTRY32W tEntry = {0};
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("Failed to create snapshot");
	}
	tEntry.dwSize = sizeof(PROCESSENTRY32W);
	for (BOOL success = Process32FirstW(hSnapshot, &tEntry); success == TRUE;
		 success = Process32NextW(hSnapshot, &tEntry))
	{
		if (processName.compare(tEntry.szExeFile) == 0)
		{
			processId = tEntry.th32ProcessID;
			break;
		}
	}
	CloseHandle(hSnapshot);
	return processId;
}

HANDLE Xash::System::GetProcessHandleById(DWORD processId)
{
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (processHandle == NULL)
	{
		throw std::runtime_error("Failed to open process handle");
	}
	return processHandle;
}

LPVOID Xash::System::AllocateMemoryInProcess(HANDLE hProcess, SIZE_T size)
{
	LPVOID lpAddress = nullptr;

	lpAddress = VirtualAllocEx(
		hProcess, nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE
	);
	return lpAddress;
}

BOOL Xash::System::FreeMemoryInProcess(HANDLE hProcess, LPVOID lpAddress, SIZE_T size)
{
	return VirtualFreeEx(hProcess, lpAddress, size, MEM_RELEASE);
}

void Xash::System::RunThreadInProcess(
	HANDLE hProcess, LPVOID lpStartAddress, LPVOID lpParameter, SIZE_T dwStackSize,
	DWORD dwCreationFlags
)
{
	HANDLE hThread = CreateRemoteThread(
		hProcess, nullptr, dwStackSize, (LPTHREAD_START_ROUTINE)lpStartAddress,
		lpParameter, dwCreationFlags, nullptr
	);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
}

std::vector<DWORD> Xash::System::GetRunningProcessesId()
{
	PROCESSENTRY32 pe32 = {0};
	std::vector<DWORD> processesID;
	HANDLE hProcessSnap = nullptr;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("Error Toolhelp32Snapshot : INVALID_HANDLE_VALUE");
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);
	BOOL success = Process32First(hProcessSnap, &pe32);
	while (success == TRUE)
	{
		processesID.push_back(pe32.th32ProcessID);
		success = Process32Next(hProcessSnap, &pe32);
	}

	CloseHandle(hProcessSnap);
	return processesID;
}

std::string Xash::System::GetProcessNameByID(DWORD processId)
{
	std::string processName;

	HANDLE handle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId);
	if (handle != nullptr)
	{
		char buffer[MAX_PATH];
		DWORD size = sizeof(buffer);
		if (QueryFullProcessImageNameA(handle, 0, buffer, &size))
		{
			processName = buffer;
		}
		CloseHandle(handle);
	}
	return processName;
}

std::vector<std::string> Xash::System::GetRunningProcessesNames()
{
	std::vector<std::string> processesNames;
	std::vector<DWORD> processesID = GetRunningProcessesId();

	for (const auto &processID : processesID)
	{
		std::string processName = GetProcessNameByID(processID);
		size_t lastSlash = processName.find_last_of("\\");
		if (lastSlash != std::string::npos)
		{
			processName = processName.substr(lastSlash + 1);
		}
		if (!processName.empty())
		{
			processesNames.push_back(processName);
		}
	}
	return processesNames;
}
