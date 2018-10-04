/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include "OpenglApp.h"


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{

	OpenglApp app = OpenglApp();

	app.Run();
	
}