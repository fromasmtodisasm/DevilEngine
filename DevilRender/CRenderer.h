#pragma once
#define DLL
#include "IRender.h"

class CRenderer : public IRenderer
{
public:
	CRenderer();
	~CRenderer();
	
	void Init(ISystem *pSystem);

	//! Init the renderer, params are self-explanatory
	WIN_HWND Init(
		int x, int y, int width, int height, 
		unsigned int cbpp, int zbpp, int sbits, 
		bool fullscreen, 
		WIN_HINSTANCE hinst, WIN_HWND Glhwnd = 0, WIN_HDC Glhdc = 0, WIN_HGLRC hGLrc = 0, 
		bool bReInit = false);


	bool SetCurrentContext(WIN_HWND hWnd);
	bool CreateContext(WIN_HWND hWnd, bool bAllowFSAA = false);
	bool DeleteContext(WIN_HWND hWnd);

	virtual void SetCamera(CCamera *pCamera);

	void Update();
private:
	typedef struct Color
	{
		float r;
		float g;
		float b;
	};
	Color ClearColor;
	ISystem *m_pSystem;

	int m_x;
	int m_y;
	int m_width;
	int m_height;
	unsigned int m_cbpp;
	int m_zbpp;
	int m_sbits;
	bool m_fullscreen;
	WIN_HINSTANCE m_hinst;
	WIN_HWND m_Glhwnd = 0;
	WIN_HDC m_Glhdc = 0;
	WIN_HGLRC m_hGLrc = 0;
	CCamera *m_Camera;
	bool bReInit;
};
