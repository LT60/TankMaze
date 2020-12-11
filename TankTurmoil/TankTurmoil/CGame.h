#pragma once
#include"CGameMenuBackground.h"
//整个游戏
//被包含进了MainFrm.h

class CGame
{
public:
	CGame();
	~CGame();

    void SetHandle(HWND hWnd);		// 设置输出窗口的句柄

    bool EnterFrame(DWORD dwTime); 	// 进入游戏帧

    void OnMouseMove(UINT nFlags, CPoint point); // 处理鼠标移动事件

    void OnLButtonUp(UINT nFlags, CPoint point); // 处理左键抬起事件

//private:
public:
    HWND m_hWnd; // 窗口

    //游戏绘图处理
    //负责 绘画 游戏中的对象
    void GameRunDraw();
    CGameMenuBackground m_menu;

    // 输出fps
    void DrawFps(Graphics& gh);

    // 记录 游戏每秒多少帧
    int m_fps{ 0 };

};

