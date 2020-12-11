// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
//#include "framework.h"
#include "Tank.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GAME_WIN_W (800)	//全局变量：窗口宽
#define GAME_WIN_H (600)	//全局变量：窗口高

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
#define MY_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | FWS_ADDTOTITLE)
	//创建窗口：
	Create(NULL, _T("坦克大战"), MY_STYLE, CRect(0, 0, GAME_WIN_W, GAME_WIN_H));
	//设置客户区大小
	{
		CRect rcCli;
		GetClientRect(rcCli);	//获取客户区的大小

		RECT rcFrame = { 0,0,				//计算边框的大小，并设置
						m_iWidth * 2 - rcCli.right,
						m_iHeight * 2 - rcCli.bottom };
		MoveWindow(&rcFrame, TRUE);
	}
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//启动定时器
	SetTimer(ETimerIdGameLoop, 0, NULL);	//启动定时器每次都会进入游戏帧
	//将当前窗口传递给CGame类
	m_game.SetHandle(GetSafeHwnd());		//设置游戏主窗口句柄
	return 0;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)	//参数代表当前是哪一个定时器
{
	switch (nIDEvent)//区分不同的消息，处理需要处理的消息
	{
	case ETimerIdGameLoop://游戏循环ID
	{
		//记录本次时刻：
		static DWORD dwLastUpdate = GetTickCount();
		//判断时间间隔
		if (GetTickCount() - dwLastUpdate >= 20)
		{
			//进入游戏帧处理!!!【更新】!!!
			m_game.EnterFrame(GetTickCount());
			//记录时间间隔
			dwLastUpdate = GetTickCount();
		}
		//否则什么都不做
	}
	default:
		break;
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	m_game.OnMouseMove(nFlags, point); // 直接把鼠标消息转给 CGame对象
	CFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_game.OnLButtonUp(nFlags, point); // 直接把鼠标消息转给 CGame对象
	CFrameWnd::OnLButtonUp(nFlags, point);
}
