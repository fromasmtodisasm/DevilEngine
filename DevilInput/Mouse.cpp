#include "Mouse.h"
#include <Windowsx.h>
#include <sstream>
using std::stringstream;
CMouse::CMouse(void)
{
	X = Y = deltaX = deltaY = 0;
	isMouseDown = false;
	isMouseUp = true;
}

CMouse::~CMouse(void)
{
}

//! check for a mouse button pressed and held
bool CMouse::MouseDown(int p_numButton)
{
	return isMouseDown == true;
}

//! check for a mouse button pressed only once
bool CMouse::MousePressed(int p_numButton)
{
	return false;
}

//! check if the mouse button has been released
bool CMouse::MouseReleased(int p_numButton)
{
	return false;
}

//! force the mouse wheel rotation to a certain value
void CMouse::SetMouseWheelRotation(int value)
{

}

//! set/reset Directinput to exclusive mode
bool CMouse::SetExclusive(bool value,void *hwnd)
{
	return false;
}

//! get mouse X delta (left-right)
float CMouse::GetDeltaX()
{
	float d = deltaX;
	deltaX = 0;
	return d;
}

//! get mouse Y delta (up-down)
float CMouse::GetDeltaY()
{
	float d = deltaY;
	deltaY = 0;
	return d;
}

//! get mouse Z delta (mouse wheel)
float CMouse::GetDeltaZ()
{
	return 10;
}

//! set mouse inertia
void CMouse::SetInertia(float)
{

}

//! set mouse X screen corrdinate
void	CMouse::SetVScreenX(float fX)
{
	//isMouseDown = true;
	deltaX = fX -X;
	X = fX;
}

//! set mouse Y screen corrdinate
void	CMouse::SetVScreenY(float fY)
{
	deltaY = fY -Y;
	Y = fY;
}

//! get mouse X screen corrdinate
float	CMouse::GetVScreenX()
{
	return 0;
}

//! get mouse Y screen corrdinate
float	CMouse::GetVScreenY()
{
	return 0;
}

void CMouse::PreprocessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	
}
bool CMouse::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{ 
	bool res = false;
	//stringstream ss;
	switch(uMsg)
	{
		//case WM_MOUSEFIRST:
		case WM_MOUSEMOVE:
		{
			res = true;
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam);
			SetVScreenX((float)xPos);
			SetVScreenY((float)yPos);
			//ss << "x = " << xPos << ", y = " << yPos;
			//SetWindowTextA(hWnd, ss.str().c_str());
			//ss.str("");
			//switch (wParam)
			//{
			//case MK_LBUTTON:
			//	isMouseDown = true;
			//	break;
			//}
			break;

		}
		 case WM_LBUTTONDOWN:
			 if (MK_LBUTTON == wParam)
			 {
				if (isMousePressed)
					SetMouseDown(0);
			 }
			SetMouseDown(0);
			 break;
		 case WM_LBUTTONUP:
			 SetMouseUp(0);
			 //if (MK_LBUTTON == wParam)
				//SetMouseUp(0);
			 break;
		 case WM_LBUTTONDBLCLK:
		 case WM_RBUTTONDOWN:
		 case WM_RBUTTONUP:
		 case WM_RBUTTONDBLCLK:
		 case WM_MBUTTONDOWN:
		 case WM_MBUTTONUP:
		 case WM_MBUTTONDBLCLK:
			res = false;
			break;
	}
	return res;
}

void CMouse::SetMouseDown(int b)
{
	isMouseDown = true;
	isMouseUp = false;
}
void CMouse::SetMouseUp(int b)
{
	isMouseDown = false;
	isMouseUp = true;
	isMousePressed = false;
}
