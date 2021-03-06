﻿
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "CGame.h"

class CMainFrame : public CFrameWnd
{

public:
    CMainFrame();
protected:
    DECLARE_DYNAMIC(CMainFrame)

    // 特性 : 类的公共成员
public:

    // 操作 : 类的公共成员
public:

    // 重写 : 类的公共成员
public:

    // 实现 : 类的共共成员
public:
    virtual ~CMainFrame();

    // 生成的消息映射方法
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()

    int m_iWidth{ 800 }; 					// 客户区的大小
    int m_iHeight{ 600 };

    enum ETimerId { ETimerIdGameLoop = 1 }; // 定时器 ID

    CGame m_game; 							// 游戏对象 : 注意,此处使用了CGame类
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);	// 定时器消息处理函数
    afx_msg void OnMouseMove(UINT nFlags, CPoint point); // 鼠标移动消息处理函数
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point); // 鼠标左键抬起函数
};
