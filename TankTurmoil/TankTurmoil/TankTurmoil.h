﻿
// TankTurmoil.h: TankTurmoil 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CTankTurmoilApp:
// 有关此类的实现，请参阅 TankTurmoil.cpp
//

class CTankTurmoilApp : public CWinApp
{
public:
	CTankTurmoilApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	// 引入 GDIPlus 所需要的变量
	ULONG_PTR m_tokenGdiplus;
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartupOutput output;

};

extern CTankTurmoilApp theApp;
