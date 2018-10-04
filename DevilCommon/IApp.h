#pragma once

#ifdef WIN32
	#ifdef DEVILAPP_EXPORTS
		#define DEVILAPP_API __declspec(dllexport)
	#else
		#define DEVILAPP_API __declspec(dllimport)
	#endif
#else
	#define DEVILAPP_API
#endif

#include "ISystem.h"

interface IApp
{
	virtual void Init(ISystem *system) = 0;
	virtual int Run() = 0;
	virtual int Update() = 0;
};

typedef IApp* (*PFNCREATEAPPINSTANCE)();
// interface of the DLL
extern "C" DEVILAPP_API IApp* CreateApp();