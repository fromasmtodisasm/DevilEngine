#include <windows.h>
#include "IBaseWindow.h"

class BaseWindow : public IBaseWindow
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BaseWindow();
	HWND Create(
		PCSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle,
		int x,
		int y,
		int nWidth,
		int nHeight,
		HWND hWndParent,
		HMENU hMenu
	);
protected:
	virtual PCSTR  ClassName() const = 0;
	virtual void SetSize(int w, int h) = 0;
protected:
	HWND m_hwnd;
	WNDCLASS wc;
};