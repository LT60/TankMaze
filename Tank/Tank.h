﻿
// Tank.h: Tank 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CTankApp:
// 有关此类的实现，请参阅 Tank.cpp
//

class CTankApp : public CWinApp
{
public:
	CTankApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	//1.5.2.1 初始化GDIplus 1：添加初始化所需的成员变量
private:
	//引入GDIPlus所需的变量
	ULONG_PTR m_tokenGdiplus;
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartupOutput output;

};

extern CTankApp theApp;
