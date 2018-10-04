#include "System.h"

CSystem::CSystem(std::string file)
{
	m_RenderLib = "DevilRender.dll";
	m_GameLib = "DevilApp.dll";
	m_AppLib = NULL;
	m_InputLib = "DevilInput.dll";
}

CSystem::~CSystem(void)
{
}

bool CSystem::CreateGame(SGameInitParams &params )
{
	m_pIApp->Run();
	return false;
}

bool CSystem::Init()
{
	bool res = false;
	if (LoadSubSystems()) {
		m_pIInput->Init(this);
		m_pIApp->Init(this);
		m_pIRenderer->Init(this);
		res = true;
	}

	return res;
}

void CSystem::Release()
{
}

void CSystem::RenderBegin()
{
}

void CSystem::Render()
{
}

void CSystem::RenderEnd()
{
}


void CSystem::Quit()
{
}


IGame *CSystem::GetIGame()
{
	return m_pIGame;
}
ILog *CSystem::GetILog()
{
	return m_pILog;
}
IRenderer *CSystem::GetIRenderer()
{
	return m_pIRenderer;
}

IApp *CSystem::GetIApp()
{
	return m_pIApp;
}

IInput *CSystem::GetIInput()
{
	return m_pIInput;
}

void CSystem::SaveConfiguration()
{

}

void CSystem::LoadConfiguration(std::string &sFilename)
{

}

void *CSystem::GetComponent(char *system, char *entry)
{
	void *EntryPoint;
	HMODULE hModule = ::LoadLibrary(system);
	if (hModule)
	{
		EntryPoint = GetProcAddress(hModule, entry);
		if (EntryPoint)
		{		
			return EntryPoint;
		}
		else
		{
			MessageBox(NULL,"Error Load Create","Error",MB_OK);
		}
	}
	else
	{
		MessageBox(NULL,"Error Load component","Error",MB_OK);
	}	
	return NULL;		
}

bool CSystem::LoadSubSystems()
{
	CreateApp = (PFNCREATEAPPINSTANCE)GetComponent(m_GameLib, "CreateApp");
	if (CreateApp)
	{
		m_pIApp = CreateApp();
	}
	
	CreateRenderer = (PFNCREATERENDERERINTERFACE)GetComponent(m_RenderLib, "CreateRenderer");
	if (CreateRenderer)
	{
		m_pIRenderer = CreateRenderer();
	}

	CreateInput = (PFNCREATEDEVILINPUTINTERFACE)GetComponent(m_InputLib, "CreateInput");
	if (CreateRenderer)
	{
		m_pIInput = CreateInput(this);
	}
	return true;
}

bool Initialize()
{

	return true;
}

DEVILSYSTEM_API ISystem* CreateSystemInterface( SSystemInitParams &initParams )
{
	ISystem *system = new CSystem("");
	return system;
}