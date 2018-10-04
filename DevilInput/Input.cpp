#include "Input.h"
#include "Mouse.h"

CInput::CInput(void)
{
}

CInput::~CInput(void)
{
}

bool CInput::Init(ISystem *pSytem)
{
	m_pIMouse = new CMouse();
	return true;
}

IKeyboard *CInput::GetIKeyboard()
{
	return m_pIKeyboard;
}
IMouse *CInput::GetIMouse()
{
	return m_pIMouse;
}

DEVILINPUT_API IInput* CreateInput( ISystem *pSystem )
{
	return new CInput();
}
