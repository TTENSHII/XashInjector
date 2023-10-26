#include "DirectX11.hpp"
#include <stdexcept>

namespace Xash::GUI
{
	// PUBLIC METHODS

	void DirectX11::Init(HWND hwnd)
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc = CreateSwapChainDesc(hwnd);
		CreateDevice(swapChainDesc);
		InitRenderTargets();
	}

	void DirectX11::Display()
	{
		// Vsync enabled
		mDx11SwapChain->Present(1, 0);
	}

	void DirectX11::Clear()
	{
		constexpr float clearColor[] = {0.0F, 0.0F, 0.0F, 1.0F};

		mDx11DeviceContext->OMSetRenderTargets(
			1U, mDx11RenderTargetView.GetAddressOf(), nullptr
		);
		mDx11DeviceContext->ClearRenderTargetView(
			mDx11RenderTargetView.Get(), clearColor
		);
	}

	// PRIVATE METHODS

	void DirectX11::CreateDevice(DXGI_SWAP_CHAIN_DESC swapChainDesc)
	{
		UINT createDeviceFlags = 0;
		UINT featureLevelCount = 1;
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
		const D3D_FEATURE_LEVEL featureLevels[] = {featureLevel};

		HRESULT result = D3D11CreateDeviceAndSwapChain(
			nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels,
			featureLevelCount, D3D11_SDK_VERSION, &swapChainDesc, &mDx11SwapChain,
			&mDx11Device, nullptr, &mDx11DeviceContext
		);
		if (result != S_OK)
		{
			throw std::runtime_error("Failed to create dx11 device");
		}
	}

	DXGI_SWAP_CHAIN_DESC DirectX11::CreateSwapChainDesc(HWND hwnd)
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {0};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = 0;
		swapChainDesc.BufferDesc.Height = 0;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		return swapChainDesc;
	}

	void DirectX11::InitRenderTargets()
	{
		ID3D11Texture2D *backBuffer;

		mDx11SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		mDx11Device->CreateRenderTargetView(
			backBuffer, nullptr, mDx11RenderTargetView.GetAddressOf()
		);
		backBuffer->Release();
	}

} // namespace Xash::GUI
