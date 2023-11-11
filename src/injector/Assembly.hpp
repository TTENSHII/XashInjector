#pragma once

#include <vector>

namespace Xash
{
	namespace Injector
	{
		class Assembly
		{
		public:
            void ClearInstructions();
			const std::vector<uint8_t> &GetAssembly() const;

            void Ret();
			void CallRax();

			void SubRsp(uint8_t value);
			void AddRsp(uint8_t value);

			void MoveIntoRax(void *value);
			void MoveIntoRcx(void *value);
			void MoveIntoRdx(void *value);
			void MoveIntoR8(void *value);
			void MoveIntoR9(void *value);
			void MoveRaxIntoValue(void *value);

			void XorRaxRax();
			void XorRcxRcx();
			void XorRdxRdx();
			void XorR8R8();
			void XorR9R9();

			void MonoThreadAttach(void *monoAttachFunc, void *MonoDomain);

		private:
			std::vector<uint8_t> _asmInstructions;
		};
	} // namespace Injector
} // namespace Xash
