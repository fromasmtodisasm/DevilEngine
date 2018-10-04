#pragma once
#include <windows.h>


#include "BaseWindow.h"
#include <IRender.h>
#include <IMouseHandler.h>


#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3

class OpenGLWindow : public BaseWindow
{
protected:
    HDC hDC;
    HGLRC hGLRC;        
    MSG msg;
    BOOL bQuit;
	BOOL g_bPause;
	LPSTR className;
	LPSTR windowTitle;
	DWORD width;
	DWORD height;
	IRenderer *m_pIRenderer;
	IInput *m_pIInput;
//	IMouseHandler *m_pIMouseHandler;
	IMouse *m_pIMouse;
public:
	OpenGLWindow(char *Name);
	~OpenGLWindow();
	HWND Create(BaseWindow *pWindow);
	void SwapBuffers();
	int MainLoop();
public:
	void OnResize(int w, int h);
	
protected:
	bool InitWindow();
	
	bool EnableOpenGL();
	void DisableOpenGL();

public:
	PCSTR  ClassName() const;
	virtual void SetSize(int w, int h);
	LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void SetWindowSize(DWORD width, DWORD height);
	void GetWindowSize(DWORD *width, DWORD *height);
	HWND GetWindow();
	void SetWindow(HWND wnd);
	void SetRender(IRenderer *m_pIRenderer);
	void SetInputHandler(IInput *pIInput);
};
