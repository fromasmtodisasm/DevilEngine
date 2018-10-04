#pragma once
#include "Api.h"
#include "ISystem.h"

//forward declarations.
//////////////////////////////////////////////////////////////////////
typedef void*	WIN_HWND;
typedef void*	WIN_HINSTANCE;
typedef void*	WIN_HDC;
typedef void*	WIN_HGLRC;

struct CCamera
{
	float x_eye, y_eye, z_eye, cx, cy, cz, x_up, y_up, z_up;
	CCamera() : x_eye(0), y_eye(0), z_eye(0), cx(0), cy(0), cz(0), x_up(0), y_up(0), z_up(0)
	{

	}
};

struct IRenderer
{
	virtual void Update() = 0;
	virtual void Init(ISystem *pSystem) = 0;

	//! Init the renderer, params are self-explanatory
	virtual WIN_HWND Init(int x, int y, int width, int height, unsigned int cbpp, int zbpp, int sbits, bool fullscreen, WIN_HINSTANCE hinst, WIN_HWND Glhwnd = 0, WIN_HDC Glhdc = 0, WIN_HGLRC hGLrc = 0, bool bReInit = false) = 0;


	virtual bool SetCurrentContext(WIN_HWND hWnd) = 0;
	virtual bool CreateContext(WIN_HWND hWnd, bool bAllowFSAA = false) = 0;
	virtual bool DeleteContext(WIN_HWND hWnd) = 0;
	virtual void SetCamera(CCamera *pCamera) = 0;
};

//////////////////////////////////////////////////////////////////////////
// DLL Exports.
//////////////////////////////////////////////////////////////////////////
typedef IRenderer* (*PFNCREATERENDERERINTERFACE)();

// interface of the DLL
extern "C" 
{
	CALL_API IRenderer* CreateRenderer();
}