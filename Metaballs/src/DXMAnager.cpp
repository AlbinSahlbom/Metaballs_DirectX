#include "DXMAnager.h"

DXManager::DXManager()
{

	m_swapChain = std::make_unique<IDXGISwapChain>();
	m_device = std::make_unique<ID3D11Device>();
	m_deviceContext = std::make_unique<ID3D11DeviceContext>();
	m_renderTargetView = std::make_unique<ID3D11RenderTargetView>();
	m_depthStencilBuffer = std::make_unique<ID3D11Texture2D>();
	m_depthStencileState = std::make_unique<ID3D11DepthStencilState>();
	m_depthStencilView = std::make_unique<ID3D11DepthStencilView>();
	m_rasterState = std::make_unique<ID3D11RasterizerState>();
	m_alphaBlendStateEnabled = std::make_unique<ID3D11BlendState>();
	m_alphaBlendStateDisabled = std::make_unique<ID3D11BlendState>();
	m_depthStencilStateDisabled = std::make_unique<ID3D11DepthStencilState>();

	m_swapChain = 0;
	m_device = 0;
	m_deviceContext = 0;
	m_renderTargetView = 0;
	m_depthStencilBuffer = 0;
	m_depthStencileState = 0;
	m_depthStencilView = 0;
	m_rasterState = 0;
	m_alphaBlendStateEnabled = 0;
	m_alphaBlendStateDisabled = 0;
	m_depthStencilStateDisabled = 0;
}

DXManager::~DXManager()
{
	if (m_swapChain)
		m_swapChain->SetFullscreenState(false, NULL);
	if (m_alphaBlendStateEnabled)
	{
		m_alphaBlendStateEnabled->Release();
		m_alphaBlendStateEnabled = 0;
	}
	if (m_alphaBlendStateDisabled)
	{
		m_alphaBlendStateDisabled->Release();
		m_alphaBlendStateDisabled = 0;
	}
	if (m_depthStencilStateDisabled)
	{
		m_depthStencilStateDisabled->Release();
		m_depthStencilStateDisabled = 0;
	}
	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}
	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}
	if (m_depthStencileState)
	{
		m_depthStencileState->Release();
		m_depthStencileState = 0;
	}
	if (m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = 0;
	}
	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}
	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = 0;
	}
	if (m_device)
	{
		m_device->Release();
		m_device = 0;
	}
	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}
}

bool DXManager::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes;
	unsigned int numerator = 0;
	unsigned int denominator = 0;
	size_t stringLength;
	std::unique_ptr<DXGI_MODE_DESC> displayModeList;
	std::unique_ptr<DXGI_ADAPTER_DESC> adapterDesc = std::make_unique<DXGI_ADAPTER_DESC>();
	int error;
	std::unique_ptr<ID3D11Texture2D> backBufferPtr = std::make_unique<ID3D11Texture2D>();

	//store vsync settings
	m_vsync_enabled = vsync;

	//Create a DirectX graphic interface factory
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
		return false;

	//Use the factory to create an adapter for the primary graphics interface
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
		return false;

	//Enumarate the primary adapter output
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
		return false;

	//Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
		return false;

	//Create a list to hold all the possible modes for this monitor/video card combinaton
	displayModeList = std::make_unique<DXGI_MODE_DESC>(new DXGI_MODE_DESC[numModes]);

	//Fill the display mode list
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList.get());
	if (FAILED(result))
		return false;

	for (int i = 0; i < numModes; i++)
	{
		if (displayModeList.get()[i].Width == (unsigned int)screenWidth)
		{
			if (displayModeList.get()[i].Height == (unsigned int)screenHeight)
			{
				numerator = displayModeList.get()[i].RefreshRate.Numerator;
				denominator = displayModeList.get()[i].RefreshRate.Denominator;
			}
		}
	}

	if (numerator && denominator)
		return false;

	//Get the adapter description
	result = adapter->GetDesc(adapterDesc.get());
	if (FAILED(result))
		return false;

	//Store the video card memory in mbs
	m_videoCardMemmory = (int)(adapterDesc.get()->DedicatedVideoMemory / 1024 / 1024);

	//Convert the name of the video card to a character array
	error = wcstombs_s(&stringLength, m_videoCardDesc, adapterDesc.get()->Description, 128);
	if (error != 0)
		return false;

	//Release memory
	adapterOutput->Release();
	adapterOutput = 0;

	adapter->Release();
	adapter = 0;

	factory->Release();
	factory = 0;

	return true;
}

void DXManager::BeginScene(float r, float g, float b, float a)
{
}

void DXManager::EndScene()
{
}

void DXManager::EnableAlphaBlending(bool enable)
{
}

void DXManager::EnableZBuffer(bool enable)
{
}

ID3D11Device * DXManager::GetDevice()
{
	return nullptr;
}

ID3D11DeviceContext * DXManager::GetDeviceContex()
{
	return nullptr;
}

bool DXManager::InitSwapChain(HWND hwnd, bool fullscreen, int screenWidth, int screenHeight, unsigned int numerator, unsigned int denominator)
{
	return false;
}

bool DXManager::InitDepthBuffer(int screenWidth, int screenHeight)
{
	return false;
}

bool DXManager::InitDepthStencilBuffer()
{
	return false;
}

bool DXManager::InitStencilView()
{
	return false;
}

bool DXManager::InitRasterizerState()
{
	return false;
}

void DXManager::InitViewport(int screenWidth, int screenHeight)
{
}

bool DXManager::InitAlphaBlending()
{
	return false;
}

bool DXManager::InitZBuffer()
{
	return false;
}
