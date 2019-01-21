#pragma once
#ifndef _DX_MANAGER_H
#define _DX_MANAGER_H

#include <dxgi1_4.h>
#include <d3dcommon.h>
#include <d3d11_4.h>
#include <string>

#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dCompiler.lib")

class DXManager
{
public:
	DXManager();
	~DXManager();

	bool Init(int screenWidth, int screenHeioght, bool vsync, HWND hwnd, bool fullscreen);
	void BeginScene(float r, float g, float b, float a);
	void EndScene();

	void EnableAlphaBlending(bool enable);
	void EnableZBuffer(bool enable);
	
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContex();
	
private:
	bool InitSwapChain(HWND hwnd, bool fullscreen, int screenWidth, int screenHeight, unsigned int numerator, unsigned int denominator);
	bool InitDepthBuffer(int screenWidth, int screenHeight);
	bool InitDepthStencilBuffer();
	bool InitStencilView();
	bool InitRasterizerState();
	void InitViewport(int screenWidth, int screenHeight);
	bool InitAlphaBlending();
	bool InitZBuffer();

private:
	bool m_vsync_enabled;
	int m_videoCardMemmory;
	char m_videoCardDesc[128];
	IDXGISwapChain*				m_swapChain;
	ID3D11Device*				m_device;
	ID3D11DeviceContext*		m_deviceContext;
	ID3D11RenderTargetView*		m_renderTargetView;
	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11DepthStencilState*	m_depthStencilState;
	ID3D11DepthStencilView*		m_depthStencilView;
	ID3D11RasterizerState*		m_rasterState;
	ID3D11BlendState*			m_alphaEnabledBlendState;
	ID3D11BlendState*			m_alphaDisabledBlendState;
	ID3D11DepthStencilState*	m_depthDisabledStencilState;
};

#endif // !_DX_MANAGER_H
