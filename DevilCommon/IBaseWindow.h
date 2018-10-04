#pragma once
interface IBaseWindow
{
	virtual HWND GetWindow() = 0;
	virtual void SetWindow(HWND) = 0;
	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
};