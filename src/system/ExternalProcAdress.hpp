#pragma once

#include <Windows.h>
#include <psapi.h>
#include <Vector>
#include <string>

namespace Xash
{
	namespace System
	{
		// Helper class for getExternalProcAddress
		class ExternalProcAdressHelper
		{
		public:
			ExternalProcAdressHelper(HANDLE hProcess, HMODULE hModule);
			~ExternalProcAdressHelper() = default;
			LPVOID GetExternalProcessAddress(const std::string &lpProcName);

		private:
			void FindBasicInfo();
			void GetExportTable();
			void FindOptionalHeader();
			void FindExportDataDirectory();
			HANDLE _hProcess = nullptr;
			HMODULE _hModule = nullptr;
			bool _is64bits = FALSE;
			UINT_PTR _moduleBaseAddress = 0;
			IMAGE_DOS_HEADER _dosHeader = {0};
			IMAGE_FILE_HEADER _fileHeader = {0};
			std::vector<DWORD> _exportFunctionTable;
			std::vector<DWORD> _exportNameTable;
			std::vector<WORD> _exportOrdinalTable;
			IMAGE_OPTIONAL_HEADER64 _optHeader64 = {0};
			IMAGE_OPTIONAL_HEADER32 _optHeader32 = {0};
			IMAGE_DATA_DIRECTORY _dataDirectory = {0};
			IMAGE_EXPORT_DIRECTORY _exportTable = {0};
		};

		LPVOID GetExternalProcAddress(
			HANDLE hProcess, HMODULE hModule, const std::string &lpProcName
		);
	} // namespace System
} // namespace Xash
