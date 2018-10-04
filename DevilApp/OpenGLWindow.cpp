#include "OpenGLWindow.h"
#include <gl/gl.h>
#include <gl/GLU.h>
#include <Windowsx.h>



//#include <sstream>
//using std::stringstream;

#include "resource.h"
OpenGLWindow::OpenGLWindow(char *Name) : m_pIRenderer(NULL), m_pIMouse(NULL), bQuit(false), g_bPause(false)
{

	windowTitle = Name;
	className = "OpenglWindow";
	
	
}

HWND OpenGLWindow::Create(BaseWindow *pWindow)
{
	DWORD windowStyle = WS_BORDER | WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	if (pWindow)
		windowStyle = WS_CHILD | WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_BORDER | WS_THICKFRAME;
	HMENU menu = CreateMenu();
	/* create main window */
	m_hwnd = BaseWindow::Create(
		windowTitle,
		windowStyle,
		0,0,0, 
		width, height,
		pWindow ? pWindow->GetWindow() : NULL,
		menu
	);

	if (pWindow)
		EnableOpenGL();
	return m_hwnd;
}

OpenGLWindow::~OpenGLWindow()
{
	DisableOpenGL();
	/* destroy the window explicitly */
    DestroyWindow (m_hwnd);
	
}

void OpenGLWindow::SwapBuffers()
{
	::SwapBuffers(hDC);
}

void OpenGLWindow::SetSize(int w, int h)
{
	width = w;
	height = h;

}

void OpenGLWindow::OnResize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	//gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool OpenGLWindow::InitWindow()
{
	return(true);
}

int OpenGLWindow::MainLoop()
{
	//ShowWindow(m_hwnd,	SW_MAXIMIZE);
	    /* program main loop */
   // while (!bQuit)
   // {
   //     /* check for messages */
   //     if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
   //     {
   //         /* handle or dispatch messages */
   //         if (msg.message == WM_QUIT)
   //         {
   //             bQuit = TRUE;
   //         }
   //         else
   //         {
   //             TranslateMessage (&msg);
   //             DispatchMessage (&msg);
   //         }
   //     }
   //     else
   //     {
   //         /* OpenGL animation code goes here */
   //         render->Update();
			//::SwapBuffers(hDC);
			//Sleep(1);
   //     }
   // }
   // return msg.wParam;
	return 0;
}

/*******************
 * Enable OpenGL
 *
 *******************/
bool OpenGLWindow::EnableOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd = { 0 };
    int iFormat;

    /* get the device context (DC) */
    hDC = GetDC (m_hwnd);

    /* set the pixel format for the DC */
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (hDC, &pfd);
    SetPixelFormat (hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
	hGLRC = wglCreateContext(hDC);
	if (!hGLRC)
	{
		MessageBox(m_hwnd, "wglCreateContext() failed", "Error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	if (!wglMakeCurrent(hDC, hGLRC))
	{
		MessageBox(m_hwnd, "wglMakeCurrent() failed", "Error", MB_ICONERROR | MB_OK);
		exit(1);
	}

}

void OpenGLWindow::DisableOpenGL()
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hGLRC);
    ReleaseDC (m_hwnd, hDC);
}

PCSTR OpenGLWindow::ClassName() const
{
	return className;
}

LRESULT OpenGLWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	LONG Result;
	if (m_pIMouse)
	{
		//m_pIMouse->PreprocessMessage(m_hwnd, message, wParam, lParam);
	}
	switch (message)
	{
	case WM_CREATE:
		{
			return 0;
		}
	case WM_CLOSE:
		PostQuitMessage(0);
		DestroyWindow(m_hwnd);
		return 0;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		case VK_PAUSE:
			//g_bPause = true;
			break;
		}
		return 0;

	case WM_COMMAND:
		switch (wParam)
		{
		case FILE_MENU_EXIT:
			DestroyWindow(this->m_hwnd);
			break;
		case FILE_MENU_OPEN:
		{
			OPENFILENAME ofn;       // common dialog box structure
			TCHAR szFile[260] = { 0 };       // if using TCHAR macros

			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = m_hwnd;;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&ofn) == TRUE)
			{
				// use ofn.lpstrFile
			}
		}
		default:
			break;
		}

	case WM_SIZE:
		OnResize(LOWORD(lParam), HIWORD(lParam));
		return 0;

	default:
		{
			if (m_pIMouse && m_pIMouse->HandleMessage(m_hwnd, message, wParam, lParam, &Result))
			{
				return Result;
			}
			else	
			{
				return DefWindowProc(m_hwnd, message, wParam, lParam);
			}
		}
	}
}

void OpenGLWindow::SetWindowSize(DWORD width, DWORD height)
{
	this->width = width;
	this->height = height;
}

void OpenGLWindow::GetWindowSize(DWORD *width, DWORD *height)
{
	*width = this->width;
	*height = this->height;
}

HWND OpenGLWindow::GetWindow()
{
	return m_hwnd;
}
void OpenGLWindow::SetWindow(HWND wnd)
{
	m_hwnd = wnd;
}

void OpenGLWindow::SetRender(IRenderer *m_pIRenderer)
{
	this->m_pIRenderer = m_pIRenderer;
}

void OpenGLWindow::SetInputHandler(IInput *pIInput)
{
	m_pIInput = pIInput;
	m_pIMouse = m_pIInput->GetIMouse();
	POINT p;
	if (GetCursorPos(&p))
	{
		//cursor position now in p.x and p.y
		m_pIMouse->SetVScreenX((float)p.x);
		m_pIMouse->SetVScreenY((float)p.y);
	}
}