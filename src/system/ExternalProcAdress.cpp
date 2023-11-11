#include <stdexcept>
#include "ExternalProcAdress.hpp"

namespace Xash::System
{
	ExternalProcAdressHelper::ExternalProcAdressHelper(HANDLE hProcess, HMODULE hModule)
		: _hProcess(hProcess), _hModule(hModule)
	{
		if (hProcess == nullptr || hModule == nullptr)
		{
			throw std::runtime_error("Error: hProcess or hModule is nullptr");
		}
		FindBasicInfo();
		FindOptionalHeader();
		FindExportDataDirectory();
		GetExportTable();
	}

	LPVOID ExternalProcAdressHelper::GetExternalProcessAddress(const std::string &lpProcName)
	{
		std::string currentFuncName;
		CHAR currentChar = ' ';

		for (DWORD i = 0; i < _exportTable.NumberOfNames; ++i)
		{
			currentChar = ' ';
			currentFuncName.clear();
			for (UINT_PTR j = 0; currentChar != '\0' && j < MAX_PATH; ++j)
			{
				if (!ReadProcessMemory(
						_hProcess,
						(LPCVOID)(_moduleBaseAddress + _exportNameTable[i] + j),
						&currentChar, sizeof(currentChar), NULL
					))
				{
					throw std::runtime_error("ReadProcessMemory failed");
				}
				currentFuncName.push_back(currentChar);
			}
			if (currentFuncName.find(lpProcName) != std::string::npos)
			{
				LPVOID TempReturn =
					(LPVOID)(_moduleBaseAddress
							 + _exportFunctionTable[_exportOrdinalTable[i]]);
				return TempReturn;
			}
		}
		return nullptr;
	}

	void ExternalProcAdressHelper::FindBasicInfo()
	{
		DWORD signature = 0;
		MODULEINFO moduleInfo = {0};

		if (!GetModuleInformation(_hProcess, _hModule, &moduleInfo, sizeof(moduleInfo)))
		{
			throw std::runtime_error("GetModuleInformation failed");
		}
		_moduleBaseAddress = (UINT_PTR)moduleInfo.lpBaseOfDll;
		if (!ReadProcessMemory(
				_hProcess, (LPCVOID)_moduleBaseAddress, &_dosHeader, sizeof(_dosHeader),
				NULL
			)
			|| _dosHeader.e_magic != IMAGE_DOS_SIGNATURE)
		{
			throw std::runtime_error("Error: DOS signature invalid");
		}
		if (!ReadProcessMemory(
				_hProcess, (LPCVOID)(_moduleBaseAddress + _dosHeader.e_lfanew),
				&signature, sizeof(DWORD), NULL
			)
			|| signature != IMAGE_NT_SIGNATURE)
		{
			throw std::runtime_error("Error: Signature invalid");
		}
		if (!ReadProcessMemory(
				_hProcess,
				(LPCVOID)(_moduleBaseAddress + _dosHeader.e_lfanew + sizeof(DWORD)),
				&_fileHeader, sizeof(_fileHeader), NULL
			))
		{
			throw std::runtime_error("ReadProcessMemory failed");
		}
		if (_fileHeader.SizeOfOptionalHeader == sizeof(_optHeader64))
		{
			_is64bits = TRUE;
		}
		else if (_fileHeader.SizeOfOptionalHeader == sizeof(_optHeader32))
		{
			_is64bits = FALSE;
		}
		else
		{
			throw std::runtime_error("Unknown module type");
		}
	}

	void ExternalProcAdressHelper::FindOptionalHeader()
	{
		if (_is64bits)
		{
			if (!ReadProcessMemory(
					_hProcess,
					(LPCVOID)(_moduleBaseAddress + _dosHeader.e_lfanew + sizeof(DWORD)
							  + sizeof(IMAGE_FILE_HEADER)),
					&_optHeader64, _fileHeader.SizeOfOptionalHeader, NULL
				)
				|| _optHeader64.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
			{
				throw std::runtime_error("ReadProcessMemory failed");
			}
		}
		else
		{
			if (!ReadProcessMemory(
					_hProcess,
					(LPCVOID)(_moduleBaseAddress + _dosHeader.e_lfanew + sizeof(DWORD)
							  + sizeof(IMAGE_FILE_HEADER)),
					&_optHeader32, _fileHeader.SizeOfOptionalHeader, NULL
				)
				|| _optHeader32.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
			{
				throw std::runtime_error("ReadProcessMemory failed");
			}
		}
	}

	void ExternalProcAdressHelper::FindExportDataDirectory()
	{
		if (_is64bits
			&& _optHeader64.NumberOfRvaAndSizes >= IMAGE_DIRECTORY_ENTRY_EXPORT + 1)
		{
			_dataDirectory.VirtualAddress =
				(_optHeader64.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).VirtualAddress;
			_dataDirectory.Size =
				(_optHeader64.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).Size;
		}
		else if (_optHeader32.NumberOfRvaAndSizes >= IMAGE_DIRECTORY_ENTRY_EXPORT + 1)
		{
			_dataDirectory.VirtualAddress =
				(_optHeader32.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).VirtualAddress;
			_dataDirectory.Size =
				(_optHeader32.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).Size;
		}
		else
		{
			throw std::runtime_error("ReadProcessMemory failed");
		}
	}

	void ExternalProcAdressHelper::GetExportTable()
	{
		UINT_PTR exportFunctionTable = 0;
		UINT_PTR exportNameTable = 0;
		UINT_PTR exportOrdinalTable = 0;
		if (!ReadProcessMemory(
				_hProcess, (LPCVOID)(_moduleBaseAddress + _dataDirectory.VirtualAddress),
				&_exportTable, sizeof(_exportTable), NULL
			))
		{
			throw std::runtime_error("ReadProcessMemory failed");
		}
		exportFunctionTable = _moduleBaseAddress + _exportTable.AddressOfFunctions;
		exportNameTable = _moduleBaseAddress + _exportTable.AddressOfNames;
		exportOrdinalTable = _moduleBaseAddress + _exportTable.AddressOfNameOrdinals;
		_exportFunctionTable.resize(_exportTable.NumberOfFunctions);
		_exportNameTable.resize(_exportTable.NumberOfNames);
		_exportOrdinalTable.resize(_exportTable.NumberOfNames);
		if (!ReadProcessMemory(
				_hProcess, (LPCVOID)exportFunctionTable, _exportFunctionTable.data(),
				_exportTable.NumberOfFunctions * sizeof(DWORD), NULL
			))
		{
			throw std::runtime_error("ReadProcessMemory failed");
		}
		if (!ReadProcessMemory(
				_hProcess, (LPCVOID)exportNameTable, _exportNameTable.data(),
				_exportTable.NumberOfNames * sizeof(DWORD), NULL
			))
		{
			throw std::runtime_error("ReadProcessMemory failed");
		}
		if (!ReadProcessMemory(
				_hProcess, (LPCVOID)exportOrdinalTable, _exportOrdinalTable.data(),
				_exportTable.NumberOfNames * sizeof(WORD), NULL
			))
		{
			throw std::runtime_error("ReadProcessMemory failed");
		}
	}

    LPVOID GetExternalProcAddress(HANDLE hProcess, HMODULE hModule, const std::string &lpProcName)
    {
        ExternalProcAdressHelper helper(hProcess, hModule);
        return helper.GetExternalProcessAddress(lpProcName);
    }

} // namespace Xash::System
