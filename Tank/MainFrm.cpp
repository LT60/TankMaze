
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Tank.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
END_MESSAGE_MAP()

#define GAME_WIN_W (800)	//全局变量：窗口宽
#define GAME_WIN_H (600)	//全局变量：窗口高

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
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

	// 创建一个视图以占用框架的工作区
	/*if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}*/

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

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
		static DWORD dwLastUpdate = GetTickCount64();
		//判断时间间隔
		if (GetTickCount64() - dwLastUpdate >= 20)
		{
			//进入游戏帧处理【更新】
			m_game.EnterFrame(GetTickCount64());
			//记录时间间隔
			dwLastUpdate = GetTickCount64();
		}
		//否则什么都不做
	}
	default:
		break;
	}
	CFrameWnd::OnTimer(nIDEvent);
}

/*
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

*/
// CMainFrame 消息处理程序

/*
	
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
// 将焦点前移到视图窗口
m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

*/