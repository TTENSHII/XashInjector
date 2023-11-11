#include "Assembly.hpp"

namespace Xash
{
	namespace Injector
	{
		void Assembly::ClearInstructions()
		{
			_asmInstructions.clear();
		}

		const std::vector<uint8_t> &Assembly::GetAssembly() const
		{
			return _asmInstructions;
		}

		void Assembly::Ret()
		{
			_asmInstructions.push_back(0xC3);
		}

		void Assembly::CallRax()
		{
			_asmInstructions.push_back(0xFF);
			_asmInstructions.push_back(0xD0);
		}

		void Assembly::SubRsp(uint8_t value)
		{
			_asmInstructions.push_back(0x48);
			_asmInstructions.push_back(0x83);
			_asmInstructions.push_back(0xEC);
			_asmInstructions.push_back(value);
		}

		void Assembly::AddRsp(uint8_t value)
		{
			_asmInstructions.push_back(0x48);
			_asmInstructions.push_back(0x83);
			_asmInstructions.push_back(0xC4);
			_asmInstructions.push_back(value);
		}

		void Assembly::MoveIntoRax(void *value)
		{
			_asmInstructions.push_back(0x48);
			_asmInstructions.push_back(0xB8);
			_asmInstructions.insert(
				_asmInstructions.end(), (uint8_t *)&value, (uint8_t *)&value + sizeof(void *)
			);
		}

		void Assembly::MoveRaxIntoValue(void *value)
		{
			_asmInstructions.push_back(0x48);
			_asmInstructions.push_back(0xA3);
			_asmInstructions.insert(
				_asmInstructions.end(), (uint8_t *)&value, (uint8_t *)&value + sizeof(void *)
			);
		}

		void Assembly::XorRaxRax()
		{
			_asmInstructions.push_back(0x48);
			_asmInstructions.push_back(0x31);
			_asmInstructions.push_back(0xC0);
		}

		void Assembly::XorRcxRcx()
		{
			_asmInstructions.push_back(0x48);
			_asmInstructions.push_back(0x31);
			_asmInstructions.push_back(0xC9);
		}

		void Assembly::XorRdxRdx()
		{
			_asmInstructions.push_back(0x48);
			_asmInstructions.push_back(0x31);
			_asmInstructions.push_back(0xD2);
		}

		void Assembly::XorR8R8()
		{
			_asmInstructions.push_back(0x4D);
			_asmInstructions.push_back(0x31);
			_asmInstructions.push_back(0xC0);
		}

		void Assembly::XorR9R9()
		{
			_asmInstructions.push_back(0x4D);
			_asmInstructions.push_back(0x31);
			_asmInstructions.push_back(0xC9);
		}

		void Assembly::MoveIntoRcx(void *value)
		{
			_asmInstructions.push_back(0x48);
			_asmInstructions.push_back(0xB9);
			_asmInstructions.insert(
				_asmInstructions.end(), (uint8_t *)&value, (uint8_t *)&value + sizeof(void *)
			);
		}

		void Assembly::MoveIntoRdx(void *value)
		{
			_asmInstructions.push_back(0x48);
			_asmInstructions.push_back(0xBA);
			_asmInstructions.insert(
				_asmInstructions.end(), (uint8_t *)&value, (uint8_t *)&value + sizeof(void *)
			);
		}

		void Assembly::MoveIntoR8(void *value)
		{
			_asmInstructions.push_back(0x49);
			_asmInstructions.push_back(0xB8);
			_asmInstructions.insert(
				_asmInstructions.end(), (uint8_t *)&value, (uint8_t *)&value + sizeof(void *)
			);
		}

		void Assembly::MoveIntoR9(void *value)
		{
			_asmInstructions.push_back(0x49);
			_asmInstructions.push_back(0xB9);
			_asmInstructions.insert(
				_asmInstructions.end(), (uint8_t *)&value, (uint8_t *)&value + sizeof(void *)
			);
		}

		void Assembly::MonoThreadAttach(void *monoAttachFunc, void *MonoDomain)
		{
			MoveIntoRax(monoAttachFunc);
			MoveIntoRcx(MonoDomain);
			CallRax();
		}
	} // namespace Injector
} // namespace Xash
