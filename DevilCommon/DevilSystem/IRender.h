#pragma once
#include "Api.h"

struct IRenderer
{
	virtual void Render() = 0;
	virtual void Init() = 0;
};

//////////////////////////////////////////////////////////////////////////
// DLL Exports.
//////////////////////////////////////////////////////////////////////////
typedef IRenderer* (*PFNCREATERENDERERINTERFACE)();

// interface of the DLL
extern "C" 
{
	CALL_API IRenderer* CreateRenderer();
}