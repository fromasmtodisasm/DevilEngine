#pragma once
#include <IInput.h>

class CInput :
	public IInput
{
public:
	CInput(void);
	~CInput(void);

	bool Init(ISystem *pSytem);
	IKeyboard *GetIKeyboard();
	IMouse * GetIMouse();

private:
	IKeyboard *m_pIKeyboard;
	IMouse *m_pIMouse;
};
