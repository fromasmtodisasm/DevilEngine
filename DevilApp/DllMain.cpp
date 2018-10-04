#include <windows.h>

extern "C" HINSTANCE g_hinstDLL;
HINSTANCE g_hinstDLL;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)  
{
	switch( fdwReason ){
		case DLL_PROCESS_ATTACH:
			g_hinstDLL = hinstDLL;
			break;
		case DLL_THREAD_ATTACH:         

			break;        
		case DLL_THREAD_DETACH:

			break;
		case DLL_PROCESS_DETACH:

			break;    
	}    
	return TRUE;  
}