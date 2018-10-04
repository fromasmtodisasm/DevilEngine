#include "OpenGLWindow.h"
#include <IApp.h>
#include <IRender.h>

class OpenglApp : public IApp
{
public:
	OpenglApp();
	~OpenglApp();
	void Render();
	void OnResize(int w, int h);
	void OnActivate(int flag);
	int Run();
	void Init(ISystem *system);
	int Update();
private:
	IRenderer *LoadRenderer();
private:
	OpenGLWindow *mainWindow;
	OpenGLWindow *openGLRenderingWindow_1, *openGLRenderingWindow_2;
	IRenderer *m_pIRenderer;
	ISystem *system;
	CCamera m_Camera;
};
