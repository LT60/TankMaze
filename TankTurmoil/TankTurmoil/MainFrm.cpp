#include "pch.h"
#include "TankTurmoil.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/********************************************************************************/
#define GAME_WIN_W (800)                      // 全局变量:窗口宽
#define GAME_WIN_H (600)                      // 全局变量:窗口高


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)    // VS2015自动生成代码

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)    // VS2015自动生成代码
    ON_WM_CREATE()
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
        CRect rtDesk;
        CRect rtDlg;
        ::GetWindowRect(::GetDesktopWindow(), &rtDesk);
        GetWindowRect(&rtDlg);
        int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
        int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
        
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

    return 0;
}
