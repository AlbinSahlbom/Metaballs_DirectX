#pragma once
#ifndef _DX_MANAGER_H
#define _DX_MANAGER_H

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <string>

class DXManager
{
public:
	DXManager();
	~DXManager();

	bool Initialize(int screenWidth, int screenHeioght, bool vsync, HWND hwnd, bool fullscreen);
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
	std::string m_videoCardDesc;
	std::unique_ptr<IDXGISwapChain>				m_swapChain;
	std::unique_ptr<ID3D11Device>				m_device;
	std::unique_ptr<ID3D11DeviceContext>		m_deviceContext;
	std::unique_ptr<ID3D11RenderTargetView>		m_renderTargetView;
	std::unique_ptr<ID3D11Texture2D>			m_depthStencilBuffer;
	std::unique_ptr<ID3D11DepthStencilState>	m_depthStencileState;
	std::unique_ptr<ID3D11DepthStencilView>		m_depthStencilView;
	std::unique_ptr<ID3D11RasterizerState>		m_rasterState;
	std::unique_ptr<ID3D11BlendState>			m_alphaBlendStateEnabled;
	std::unique_ptr<ID3D11BlendState>			m_alphaBlendStateDisabled;
	std::unique_ptr<ID3D11DepthStencilState>	m_depthStencilStateDisabled;
};

#endif // !_DX_MANAGER_H
