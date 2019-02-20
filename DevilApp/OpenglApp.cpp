#include "OpenglApp.h"
#include <vector>

#include "resource1.h"

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
	mainWindow->setMenuName(MAKEINTRESOURCE(IDR_MENU1));
	mainWindow->Create(NULL);
	openGLRenderingWindow_1->SetSize(700, 700);
	openGLRenderingWindow_1->Create(mainWindow);

	m_pIRenderer->Init(system);

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
	
	openGLRenderingWindow_1->SetRender(m_pIRenderer);
	openGLRenderingWindow_1->SetInputHandler(system->GetIInput());
}

DEVILAPP_API IApp *CreateApp()
{
	return new OpenglApp();
	 //app;
}