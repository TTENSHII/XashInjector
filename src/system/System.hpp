#pragma once

#include <Windows.h>
#include <psapi.h>
#include <TlHelp32.h>
#include <Vector>
#include <string>

namespace Xash
{
	namespace System
	{
		HMODULE GetModuleByKeyword(HANDLE hProcess, const std::wstring &keyword);

		DWORD GetProcessIdByName(const std::wstring &processName);

		HANDLE GetProcessHandleById(DWORD processId);

		LPVOID AllocateMemoryInProcess(HANDLE hProcess, SIZE_T size);

		BOOL FreeMemoryInProcess(HANDLE hProcess, LPVOID lpAddress, SIZE_T size);

		std::vector<DWORD> GetRunningProcessesId();

		std::vector<std::string> GetRunningProcessesNames();

		std::string GetProcessNameByID(DWORD processId);

		void RunThreadInProcess(
			HANDLE hProcess, LPVOID lpStartAddress, LPVOID lpParameter = nullptr,
			SIZE_T dwStackSize = 0, DWORD dwCreationFlags = 0
		);

		template <typename T>
		void WriteMemoryInProcess(HANDLE hProcess, LPVOID lpAddress, T value, SIZE_T size)
		{
			SIZE_T bytesWritten = 0;

			BOOL res =
				WriteProcessMemory(hProcess, lpAddress, value, size, &bytesWritten);
			if (res == FALSE || bytesWritten != size)
			{
				throw std::runtime_error("Error: writeMemoryInProcess failed");
			}
		}

		template <typename T>
		LPVOID AllocateAndWriteMemoryInProcess(HANDLE hProcess, T value, SIZE_T size)
		{
			LPVOID lpAddress = AllocateMemoryInProcess(hProcess, size);
			WriteMemoryInProcess(hProcess, lpAddress, value, size);
			return lpAddress;
		}

		template <typename T>
		T ReadMemoryInProcess(HANDLE hProcess, LPVOID lpBaseAddress, SIZE_T size)
		{
			T value;
			SIZE_T bytesRead = 0;

			ReadProcessMemory(hProcess, lpBaseAddress, &value, size, &bytesRead);

			if (bytesRead != size)
			{
				throw std::runtime_error("Error: readMemoryInProcess failed");
			}
			return value;
		}

	} // namespace System
} // namespace Xash
