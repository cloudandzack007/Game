
// Game_LTY.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGame_LTYApp:
// �йش����ʵ�֣������ Game_LTY.cpp
//

class CGame_LTYApp : public CWinApp
{
public:
	CGame_LTYApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGame_LTYApp theApp;