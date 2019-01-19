#pragma once
#ifndef _FRAMEWORK_H
#define _FRAMEWORK_K

#include <string>
#include <Windows.h>

class FrameWork
{
public:
	FrameWork();
	~FrameWork();

	bool Initialize();
	void Run();

	void SetFullScreen(bool isFullScreen);
	bool GetIsFullScreen();

private:
	bool CreateDXWindow(std::string windowTitle, int x, int y, int width, int height);
	
	std::string m_applicationName;
	HINSTANCE m_hInstance;
	bool m_isFullScreen;
};

#endif // !_FRAMEWORK_H

