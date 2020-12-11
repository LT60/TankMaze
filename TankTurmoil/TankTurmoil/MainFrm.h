#pragma once
//代表游戏的主窗口，也是游戏一启动就建立的窗口
class CMainFrame : public CFrameWnd
{

public:
    CMainFrame();
protected:
    DECLARE_DYNAMIC(CMainFrame)

    // 特性
public:

    // 操作
public:

    // 重写
public:

    // 实现
public:
    virtual ~CMainFrame();

    // 生成的消息映射方法
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()

    int m_iWidth{ 800 };   // 客户区的宽
    int m_iHeight{ 600 };  // 客户区的高

}; 
