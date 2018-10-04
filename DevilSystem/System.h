#pragma once

#include <ISystem.h>
#include <IRender.h>
#include <IApp.h>
#include <I3DEngine.h>
#include <IInput.h>

class CSystem :	public ISystem
{
	//HMODULE openglApp;
	IGame *m_pIGame;
	ILog *m_pILog;
	IRenderer *m_pIRenderer;
	IApp *m_pIApp;
	IInput *m_pIInput;
	I3DEngine *m_pI3Dengine;
	//****************************
	PFNCREATERENDERERINTERFACE CreateRenderer;
	PFNCREATEAPPINSTANCE CreateApp;
	PFNCREATEDEVILINPUTINTERFACE CreateInput;

public:
	CSystem(std::string file);
	~CSystem();
	
	// Loads GameDLL and creates game instance.
	 bool CreateGame(SGameInitParams &params );
	
	bool Init();

	// Release ISystem.
	 void Release();
	 void *GetComponent(char *system, char* entry);

	// Begin rendering frame.
	 void	RenderBegin();
	// Render subsystems.
	 void	Render();
	// End rendering frame and swap back buffer.
	 void	RenderEnd();

	// Quit the appliacation
	 void	Quit();

	// return the related subsystem interface
	 IGame					*GetIGame();
	 ILog					*GetILog();
	 IRenderer				*GetIRenderer();
	 IApp					*GetIApp();
	 IInput					*GetIInput();
	//////////////////////////////////////////////////////////////////////////
	// Configuration.
	//////////////////////////////////////////////////////////////////////////
	// Saves system configuration.
	 void SaveConfiguration();
	// Loads system configuration
	 void LoadConfiguration(std::string &sFilename);

	 /////////////////////////////////////////////////////////////////////////
	 bool Initialize();

private:
	bool LoadSubSystems();

private:
	char *m_RenderLib;
	char *m_GameLib;
	char *m_AppLib;
	char *m_InputLib;

};
