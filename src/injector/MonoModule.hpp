#pragma once

#include <Windows.h>
#include <unordered_map>
#include <string>

namespace Xash
{
	namespace Injector
	{
		class MonoModule
		{
		public:
			MonoModule(HANDLE hProcess);
			~MonoModule() = default;

			bool LoadMod();
			bool UnLoadMod();

		private:
			void FindMonoFunctions();
			void FindMonoModule();

			void GetMonoDomain();
			void GetMonoAssembly();
			void GetMonoImage();
			void GetMonoClass();
			void GetMonoInitMethod();
			void GetMonoUnLoadMethod();

			void MonoRuntimeInvoke(LPVOID method);

			HANDLE	_hProcess;
			HMODULE _monoModule;

			LPVOID _monoRootDomain = nullptr;
			LPVOID _monoAssembly = nullptr;
			LPVOID _monoImage = nullptr;
			LPVOID _monoClass = nullptr;
			LPVOID _monoInitMethod = nullptr;
			LPVOID _monoUnloadMethod = nullptr;

            std::string _modPath = "";
			std::string _modNamespace = "";
			std::string _modClass = "";
			std::string _modInitMethod = "";
			std::string _modUnloadMethod = "";
			std::string _targetedProcessName = "";

			std::unordered_map<std::string, LPVOID> _monoFunctions;
		};
	} // namespace Injector
} // namespace Xash
