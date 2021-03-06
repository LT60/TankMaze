﻿#include "pch.h"
#include "TankTurmoil.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/********************************************************************************/
#define GAME_WIN_W (800)                      // 全局变量:窗口宽
#define GAME_WIN_H (600)                      // 全局变量:窗口高


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)    // VS2019自动生成代码

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)    // VS2019自动生成代码
    ON_WM_CREATE()
    ON_WM_TIMER()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
#define MY_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | \
        WS_MINIMIZEBOX | FWS_ADDTOTITLE)
    // 创建窗口
    Create(NULL, _T("牛坦克动荡"), MY_STYLE, CRect(0, 0, GAME_WIN_W, GAME_WIN_H));
    // 设置客户区大小
    {
        CRect rcCli;
        GetClientRect(rcCli);       // 获得客户区的大小
        
        //抄来的计算居中位置
        //https://blog.csdn.net/friendan/article/details/49688243
        CRect rtDesk;
        CRect rtDlg;
        ::GetWindowRect(::GetDesktopWindow(), &rtDesk);
        GetWindowRect(&rtDlg);
        int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
        int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
        //(将窗口变大后就没用了)
        iXpos = 0;
        iYpos = 0;
        RECT rcFrame = { iXpos, iYpos,      // 计算边框的大小，并设置
                         m_iWidth + m_iWidth - rcCli.right+iXpos,
                         m_iHeight + m_iHeight - rcCli.bottom+iYpos
        };
        MoveWindow(&rcFrame, TRUE); // 调用WindowsAPI设置窗口位置和大小
    }
}

CMainFrame::~CMainFrame()           // 析构函数
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1) {
        return -1;
    }
    SetTimer(ETimerIdGameLoop, 0, NULL); 					// 启动定时器 每次都会进入游戏帧
    m_game.SetHandle(GetSafeHwnd());						// 设置游戏主窗口句柄

    return 0;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
    switch (nIDEvent) {
    case ETimerIdGameLoop: { 							// 游戏循环ID
        static DWORD dwLastUpdate = GetTickCount();		// 记录本次时刻
        if (GetTickCount() - dwLastUpdate >= 20) { 		// 判断时间隔
            m_game.EnterFrame(GetTickCount());			// 进入游戏帧处理
            dwLastUpdate = GetTickCount();				// 记录时间间隔
        }
        // 否则什么都不做
    }
    default:
        break;
    }

    CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
    m_game.OnMouseMove(nFlags, point); 					// 直接把鼠标消息转给 CGame对象
    CFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_game.OnLButtonUp(nFlags, point); 				// 直接把鼠标消息转给 CGame对象
    CFrameWnd::OnLButtonUp(nFlags, point);
}
