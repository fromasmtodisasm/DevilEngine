#pragma once
#include <IInput.h>
#include <IWindowMessageHandler.h>

class CMouse :
	public IMouse
{
public:
	CMouse(void);
	~CMouse(void);

	//! check for a mouse button pressed and held
	virtual bool MouseDown(int p_numButton);

	//! check for a mouse button pressed only once
	virtual bool MousePressed(int p_numButton);

	//! check if the mouse button has been released
	virtual bool MouseReleased(int p_numButton);

	//! force the mouse wheel rotation to a certain value
	virtual void SetMouseWheelRotation(int value);

	//! set/reset Directinput to exclusive mode
	virtual bool SetExclusive(bool value,void *hwnd=0);

	//! get mouse X delta (left-right)
	virtual float GetDeltaX();

	//! get mouse Y delta (up-down)
	virtual float GetDeltaY();

	//! get mouse Z delta (mouse wheel)
	virtual float GetDeltaZ();

	//! set mouse inertia
	virtual void SetInertia(float);

	//! set mouse X screen corrdinate
	virtual void	SetVScreenX(float fX);

	//! set mouse Y screen corrdinate
	virtual void	SetVScreenY(float fY);

	//! get mouse X screen corrdinate
	virtual float	GetVScreenX();

	//! get mouse Y screen corrdinate
	virtual float	GetVScreenY();

	// IWindowMessageHandler interface //
	void PreprocessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

private:
	void SetMouseDown(int b);
	void SetMouseUp(int b);

private:
	float deltaX;
	float deltaY;
	float X;
	float Y;
	bool isMouseDown;
	bool isMouseUp;
	bool isMousePressed;
};
