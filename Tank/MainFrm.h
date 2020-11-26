
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame() noexcept;
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 实现
public:
	virtual ~CMainFrame();

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
//	CChildView    m_wndView;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

	//游戏窗口大小为800*600像素
	int m_iWidth{ 800 };//客户区的宽
	int m_iHeight{ 600 };//客户区的高
};


