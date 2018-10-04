#pragma once

#include "Api.h"
#include "ISystem.h"

interface IApp
{
	virtual void SetSystem(ISystem *system) = 0;
	virtual void Init() = 0;
	virtual int Run() = 0;
};

typedef IApp* (*PFNCREATEAPPINSTANCE)();
// interface of the DLL
extern "C" CALL_API IApp* CreateApp();