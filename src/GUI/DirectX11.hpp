#pragma once

#include <windows.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace Xash::GUI
{
	class DirectX11
	{
	public:
		DirectX11() = default;

		void Init(HWND hwnd);
		void Display();
		void Clear();

	private:
		void InitRenderTargets();
		void CreateDevice(DXGI_SWAP_CHAIN_DESC swapChainDesc);
		DXGI_SWAP_CHAIN_DESC CreateSwapChainDesc(HWND hwnd);

		Microsoft::WRL::ComPtr<ID3D11Device> mDx11Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDx11DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mDx11SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mDx11RenderTargetView;
	};
} // namespace Xash::GUI
