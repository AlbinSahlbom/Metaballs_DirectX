#include "DXMAnager.h"

DXManager::DXManager()
{
}

DXManager::~DXManager()
{
}

bool DXManager::Initialize(int screenWidth, int screenHeioght, bool vsync, HWND hwnd, bool fullscreen)
{
	return false;
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
