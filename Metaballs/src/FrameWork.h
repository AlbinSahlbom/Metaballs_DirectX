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

private:
	bool CreateDXWindow(std::string windowTitle, int x, int y, int width, int height);
	
	std::string m_applicationName;
	HINSTANCE m_hInstance;
};

#endif // !_FRAMEWORK_H

