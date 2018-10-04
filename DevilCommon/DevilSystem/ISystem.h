#pragma once

#ifndef SDK
	#define CRYSYSTEM_EXPORTS
#endif
#ifdef WIN32
	#ifdef CRYSYSTEM_EXPORTS
		#define CRYSYSTEM_API __declspec(dllexport)
	#else
		#define CRYSYSTEM_API __declspec(dllimport)
	#endif
#else
	#define CRYSYSTEM_API
#endif

#include "Platform.h" // Needed for LARGE_INTEGER (for consoles).
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////////////////////////////////////////////
//#include <ILog.h>

struct ISystem;
struct ILog;
struct IRenderer;
struct IConsole;
struct IProcess;
struct I3DEngine;
struct ITimer;
struct IGame;
struct IApp;

//////////////////////////////////////////////////////////////////////////
// Structure passed to Init method of ISystem interface.
struct SSystemInitParams
{
	void *hInstance;											//
	void *hWnd;														//
	char szSystemCmdLine[512];						// command line, used to execute the early commands e.g. -DEVMODE "g_gametype ASSAULT"
	ILog *pLog;														// You can specify your own ILog to be used by System.
	const char* sLogFileName;							// File name to use for log.
	bool bEditor;													// When runing in Editor mode.
	bool bPreview;												// When runing in Preview mode (Minimal initialization).
	bool bTestMode;												// When runing in Automated testing mode.
	bool bDedicatedServer;								// When runing a dedicated server.
	ISystem *pSystem;											// Pointer to existing ISystem interface, it will be reused if not NULL.

#if defined(LINUX)
	void (*pCheckFunc)(void*);							// authentication function (must be set).
#else
	void *pCheckFunc;											// authentication function (must be set).
#endif

	// Initialization defaults.
	SSystemInitParams()
	{
		hInstance = 0;
		hWnd = 0;
		memset(szSystemCmdLine,0,sizeof(szSystemCmdLine));
		pLog = 0;
		sLogFileName = 0;
		bEditor = false;
		bPreview = false;
		bTestMode = false;
		bDedicatedServer = false;
		pSystem = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// Structure passed to CreateGame method of ISystem interface.
struct SGameInitParams
{
	const char *	sGameDLL;							// Name of Game DLL. (Win32 Only)
	IGame *				pGame;								// Pointer to already created game interface.
	bool					bDedicatedServer;			// When runing a dedicated server.
	char					szGameCmdLine[256];		// command line, used to execute the console commands after game creation e.g. -DEVMODE "g_gametype ASSAULT"
	
	SGameInitParams()
	{
		sGameDLL = NULL;
		pGame = NULL;		
		bDedicatedServer = false;
		memset(szGameCmdLine,0,256);
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// Main Engine Interface
// initialize and dispatch all engine's subsystems 
struct ISystem
{
	// Loads GameDLL and creates game instance.
	virtual bool CreateGame(SGameInitParams &params ) = 0;
	
	// Release ISystem.
	virtual void Release() = 0;
	virtual void *GetComponent(char *system, char* entry) = 0;

		// Begin rendering frame.
	virtual void	RenderBegin() = 0;
	// Render subsystems.
	virtual void	Render() = 0;
	// End rendering frame and swap back buffer.
	virtual void	RenderEnd() = 0;

	// Quit the appliacation
	virtual void	Quit() = 0;

	// return the related subsystem interface
	virtual IGame						*GetIGame() = 0;
	virtual ILog						*GetILog() = 0;
	virtual IRenderer				*GetIRenderer() = 0;
	virtual IApp					*GetIApp() = 0;
	//////////////////////////////////////////////////////////////////////////
	// Configuration.
	//////////////////////////////////////////////////////////////////////////
	// Saves system configuration.
	virtual void SaveConfiguration() = 0;
	// Loads system configuration
	virtual void LoadConfiguration(std::string &sFilename)=0;
};

//////////////////////////////////////////////////////////////////////////
// CrySystem DLL Exports.
//////////////////////////////////////////////////////////////////////////
typedef ISystem* (*PFNCREATESYSTEMINTERFACE)( SSystemInitParams &initParams );

// Get the system interface (must be defined locally in each module)
extern ISystem *GetISystem();

// interface of the DLL
extern "C" 
{
	CRYSYSTEM_API ISystem* CreateSystemInterface( SSystemInitParams &initParams );
}