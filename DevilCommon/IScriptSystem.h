#pragma once

#ifdef WIN32
	#ifdef DEVILSCRIPTSYSTEM_EXPORTS
		#define DEVILSCRIPTSYSTEM_API __declspec(dllexport)
	#else
		#define DEVILSCRIPTSYSTEM_API __declspec(dllimport)
	#endif
#else
	#define DEVILSCRIPTSYSTEM_API
#endif

#include "ISystem.h"

struct IScriptSystem
{
	virtual bool Init() = 0;
	virtual int Release() = 0;
};

//////////////////////////////////////////////////////////////////////////
// DevilScriptSystem DLL Exports.
//////////////////////////////////////////////////////////////////////////
typedef IScriptSystem* (*PFNCREATESCRIPTSYSTEMINTERFACE)( ISystem *pSystem );

// interface of the DLL
extern "C" 
{
	DEVILSCRIPTSYSTEM_API IScriptSystem* CreateScriptSystem( ISystem *pSystem );
}

