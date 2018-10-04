/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <fstream>
#include <string>
#include <map>
#include "IApp.h"

#include "ISystem.h"

using namespace std;


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
	int ExitStatus = EXIT_FAILURE;

	SSystemInitParams initParams;
	ISystem *pSystem = CreateSystemInterface(initParams);
#ifdef STATIC
	app = CreateApp();
	if (app)
	{
		app->SetSystem(system);
		app->Init();
		ExitStatus = app->Run();
	}
#else
	
	pSystem->Init();
	SGameInitParams gip;
	pSystem->CreateGame(gip);
#endif
	return ExitStatus;

	
}