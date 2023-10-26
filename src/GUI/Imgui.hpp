#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>

namespace Xash::GUI
{
	class Imgui
	{
	public:
		Imgui();
		~Imgui();

        void InitWin32AndDX11(
            const HWND &window, Microsoft::WRL::ComPtr<ID3D11Device> device,
            Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext
        );
		void Draw();
		void Render();
	};
} // namespace Xash::GUI
