#include "OpenglApp.h"
#include <vector>

using std::vector;


OpenglApp::OpenglApp()
{

}

OpenglApp::~OpenglApp()
{
	
}


int OpenglApp::Run()
{
	
	mainWindow->SetSize(700,700);
	mainWindow->Create(NULL);
	openGLRenderingWindow_1->SetSize(500,500);
	openGLRenderingWindow_1->Create(mainWindow);
	//HWND statusBar = CreateStatusWindow()
	HMENU hMenu = CreateMenu();
	HMENU hFile = CreateMenu();
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFile, "File");
	AppendMenu(hFile, MF_STRING, FILE_MENU_NEW, "New");
	AppendMenu(hFile, MF_STRING, FILE_MENU_OPEN, "Open");
	AppendMenu(hFile, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFile, MF_STRING, FILE_MENU_EXIT, "Exit");
	SetMenu(mainWindow->GetWindow(), hMenu);
	//openGLRenderingWindow_2->SetSize(500, 500);
	//openGLRenderingWindow_2->Create(mainWindow);
	//HWND hButton_Exit = CreateWindowEx(
	//	0, "BUTTON", "Exit", WS_CHILD | BS_GROUPBOX | WS_VISIBLE,
	//	520, 520,
	//		50, 30, mainWindow->GetWindow(), 0, GetModuleHandle(NULL), this
	//	);
	return Update();
}

int OpenglApp::Update()
{
	bool bQuit = false;
	MSG msg;
	while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }

			//TranslateMessage(&msg);
			//DispatchMessage(&msg);
        }
        else
        {
            /* OpenGL animation code goes here */
            m_pIRenderer->Update();
			openGLRenderingWindow_1->SwapBuffers();
			//openGLRenderingWindow_2->SwapBuffers();
			//Sleep(1);
        }
    }
    return msg.wParam;
}

void OpenglApp::Init(ISystem *pSystem)
{
	system = pSystem;
	mainWindow = new OpenGLWindow("OpenGL Main");
	openGLRenderingWindow_1 = new OpenGLWindow("Rendering Window 1");
	openGLRenderingWindow_2 = new OpenGLWindow("Rendering Window 2");
	m_pIRenderer = (IRenderer*)system->GetIRenderer();
	//render->Init(openGLRenderingWindow->)
	openGLRenderingWindow_1->SetRender(m_pIRenderer);
	openGLRenderingWindow_1->SetInputHandler(system->GetIInput());
}

DEVILAPP_API IApp *CreateApp()
{
	return new OpenglApp();
	 //app;
}