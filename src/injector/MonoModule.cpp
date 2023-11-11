#include <stdexcept>
#include "System.hpp"
#include "MonoModule.hpp"
#include "Assembly.hpp"
#include "ExternalProcAdress.hpp"

namespace Xash::Injector
{
	MonoModule::MonoModule(HANDLE hProcess) : _hProcess(hProcess)
	{
		FindMonoModule();
		_monoFunctions = {
			{"mono_get_root_domain", nullptr},
			{"mono_thread_attach", nullptr},
			{"mono_assembly_get_image", nullptr},
			{"mono_class_from_name", nullptr},
			{"mono_class_get_method_from_name", nullptr},
			{"mono_runtime_invoke", nullptr},
			{"mono_assembly_close", nullptr},
			{"mono_assembly_open", nullptr}
		};
		FindMonoFunctions();
	}

	void MonoModule::FindMonoModule()
	{
		const std::wstring _monoModuleKeyword = L"MonoBleedingEdge";

		_monoModule = System::GetModuleByKeyword(_hProcess, _monoModuleKeyword);
		if (_monoModule == nullptr)
		{
			throw std::runtime_error("Error: mono module not found in process");
		}
	}

	void MonoModule::FindMonoFunctions()
	{
		for (auto &[name, address] : _monoFunctions)
		{
			address = System::GetExternalProcAddress(_hProcess, _monoModule, name);
			if (address == nullptr)
			{
				throw std::runtime_error("Error: " + name + " not found in mono module");
			}
		}
	}

	bool MonoModule::LoadMod()
	{
		GetMonoDomain();
		GetMonoAssembly();
		GetMonoImage();
		GetMonoClass();
		GetMonoInitMethod();
		MonoRuntimeInvoke(_monoInitMethod);
		return true;
	}

	bool MonoModule::UnLoadMod()
	{
		GetMonoUnLoadMethod();
		MonoRuntimeInvoke(_monoUnloadMethod);
		return true;
	}

	void MonoModule::GetMonoDomain()
	{
		std::vector<uint8_t> payload;
		Assembly assembly;

		LPVOID returnValue = System::AllocateMemoryInProcess(_hProcess, sizeof(LPVOID));
		assembly.MoveIntoRax(_monoFunctions["mono_get_root_domain"]);
		assembly.CallRax();
		assembly.MoveRaxIntoValue(returnValue);
		assembly.Ret();
		payload = assembly.GetAssembly();

		LPVOID payloadAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, payload.data(), payload.size()
		);

		System::RunThreadInProcess(_hProcess, payloadAdress);

		_monoRootDomain =
			System::ReadMemoryInProcess<LPVOID>(_hProcess, returnValue, sizeof(LPVOID));
	}

	void MonoModule::GetMonoAssembly()
	{
		std::vector<uint8_t> payload;
		Assembly assembly;

		LPVOID returnValue = System::AllocateMemoryInProcess(_hProcess, sizeof(LPVOID));

		LPVOID modAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, _modPath.c_str(), _modPath.size() + 1
		);

		assembly.SubRsp(0x18);
		assembly.MonoThreadAttach(_monoFunctions["mono_thread_attach"], _monoRootDomain);
		assembly.MoveIntoRax(_monoFunctions["mono_assembly_open"]);
		assembly.MoveIntoRcx(modAdress);
		assembly.XorRdxRdx();
		assembly.CallRax();
		assembly.MoveRaxIntoValue(returnValue);
		assembly.AddRsp(0x18);
		assembly.Ret();
		payload = assembly.GetAssembly();

		LPVOID payloadAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, payload.data(), payload.size()
		);

		System::RunThreadInProcess(_hProcess, payloadAdress);
		_monoAssembly =
			System::ReadMemoryInProcess<LPVOID>(_hProcess, returnValue, sizeof(LPVOID));
	}

	void MonoModule::GetMonoImage()
	{
		std::vector<uint8_t> payload;
		Assembly assembly;

		LPVOID returnValue = System::AllocateMemoryInProcess(_hProcess, sizeof(LPVOID));
		assembly.SubRsp(0x18);
		assembly.MonoThreadAttach(_monoFunctions["mono_thread_attach"], _monoRootDomain);
		assembly.MoveIntoRax(_monoFunctions["mono_assembly_get_image"]);
		assembly.MoveIntoRcx(_monoAssembly);
		assembly.CallRax();
		assembly.AddRsp(0x18);
		assembly.MoveRaxIntoValue(returnValue);
		assembly.Ret();
		payload = assembly.GetAssembly();

		LPVOID payloadAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, payload.data(), payload.size()
		);

		System::RunThreadInProcess(_hProcess, payloadAdress);
		_monoImage =
			System::ReadMemoryInProcess<LPVOID>(_hProcess, returnValue, sizeof(LPVOID));
	}

	void MonoModule::GetMonoClass()
	{
		std::vector<uint8_t> payload;
		Assembly assembly;

		LPVOID namespaceAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, _modNamespace.c_str(), _modNamespace.size() + 1
		);
		LPVOID classNameAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, _modClass.c_str(), _modClass.size() + 1
		);

		LPVOID returnValue = System::AllocateMemoryInProcess(_hProcess, sizeof(LPVOID));
		assembly.SubRsp(0x18);
		assembly.MonoThreadAttach(_monoFunctions["mono_thread_attach"], _monoRootDomain);
		assembly.MoveIntoRax(_monoFunctions["mono_class_from_name"]);
		assembly.MoveIntoRcx(_monoImage);
		assembly.MoveIntoRdx(namespaceAdress);
		assembly.MoveIntoR8(classNameAdress);
		assembly.CallRax();
		assembly.AddRsp(0x18);
		assembly.MoveRaxIntoValue(returnValue);
		assembly.Ret();
		payload = assembly.GetAssembly();

		LPVOID payloadAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, payload.data(), payload.size()
		);

		System::RunThreadInProcess(_hProcess, payloadAdress);
		_monoClass =
			System::ReadMemoryInProcess<LPVOID>(_hProcess, returnValue, sizeof(LPVOID));
	}

	void MonoModule::GetMonoInitMethod()
	{
		std::vector<uint8_t> payload;
		Assembly assembly;

		LPVOID methodNameAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, _modInitMethod.c_str(), _modInitMethod.size() + 1
		);

		LPVOID returnValue = System::AllocateMemoryInProcess(_hProcess, sizeof(LPVOID));
		assembly.SubRsp(0x20);
		assembly.MonoThreadAttach(_monoFunctions["mono_thread_attach"], _monoRootDomain);
		assembly.MoveIntoRax(_monoFunctions["mono_class_get_method_from_name"]);
		assembly.MoveIntoRcx(_monoClass);
		assembly.MoveIntoRdx(methodNameAdress);
		assembly.XorR8R8();
		assembly.CallRax();
		assembly.AddRsp(0x20);
		assembly.MoveRaxIntoValue(returnValue);
		assembly.Ret();
		payload = assembly.GetAssembly();

		LPVOID payloadAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, payload.data(), payload.size()
		);

		System::RunThreadInProcess(_hProcess, payloadAdress);
		_monoInitMethod =
			System::ReadMemoryInProcess<LPVOID>(_hProcess, returnValue, sizeof(LPVOID));
	}

	void MonoModule::MonoRuntimeInvoke(LPVOID method)
	{
		std::vector<uint8_t> payload;
		Assembly assembly;

		assembly.SubRsp(0x18);
		assembly.MonoThreadAttach(_monoFunctions["mono_thread_attach"], _monoRootDomain);
		assembly.MoveIntoRax(_monoFunctions["mono_runtime_invoke"]);
		assembly.MoveIntoRcx(method);
		assembly.XorRdxRdx();
		assembly.XorR8R8();
		assembly.XorR9R9();
		assembly.CallRax();
		assembly.AddRsp(0x18);
		assembly.Ret();
		payload = assembly.GetAssembly();

		LPVOID payloadAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, payload.data(), payload.size()
		);

		System::RunThreadInProcess(_hProcess, payloadAdress);
		System::FreeMemoryInProcess(_hProcess, payloadAdress, payload.size());
	}

	void MonoModule::GetMonoUnLoadMethod()
	{
		std::vector<uint8_t> payload;
		Assembly assembly;

		LPVOID methodNameAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, _modUnloadMethod.c_str(), _modUnloadMethod.size() + 1
		);

		LPVOID returnValue = System::AllocateMemoryInProcess(_hProcess, sizeof(LPVOID));
		assembly.SubRsp(0x20);
		assembly.MonoThreadAttach(_monoFunctions["mono_thread_attach"], _monoRootDomain);
		assembly.MoveIntoRax(_monoFunctions["mono_class_get_method_from_name"]);
		assembly.MoveIntoRcx(_monoClass);
		assembly.MoveIntoRdx(methodNameAdress);
		assembly.XorR8R8();
		assembly.CallRax();
		assembly.AddRsp(0x20);
		assembly.MoveRaxIntoValue(returnValue);
		assembly.Ret();
		payload = assembly.GetAssembly();

		LPVOID payloadAdress = System::AllocateAndWriteMemoryInProcess(
			_hProcess, payload.data(), payload.size()
		);

		System::RunThreadInProcess(_hProcess, payloadAdress);
		_monoUnloadMethod =
			System::ReadMemoryInProcess<LPVOID>(_hProcess, returnValue, sizeof(LPVOID));
	}
} // namespace Xash::Injector
