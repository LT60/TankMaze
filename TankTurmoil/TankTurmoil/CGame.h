#pragma once
#include"CGameMenuBackground.h"
#include"CGameMenuPanel.h"
#include "TankEntry.h"
#include "Player.h"
#include "Bullet.h"
#include "Bot.h"
#include "GameMap.h"

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
    void GameRunLogic();

    CGameMenuPanel m_menuSelect;
    CGameMenuBackground m_menu;

    // 输出fps
    void DrawFps(Graphics& gh);

    // 记录 游戏每秒多少帧
    int m_fps{ 0 };

    CPlayer m_player01{ 100, 100, _T("tank_player1.png") }; // 两个玩家对象

    CPlayer m_player02{ 200, 100, _T("tank_player2.png") }; // 玩家对象2: 双人对战时才会用到

    CBot m_bot{ 300, 200, _T("tank_bot.png") };              // 一个电脑: 人机对战时用到

    std::list<CBullet> m_lstBullets;                        // 存在于地图场景中的 子弹对象数组

    CGameMap m_map{ 10, 10, 780, 580 };             //地图对象

    bool CGame::GameInitOne2Bot(); //游戏初始化，人机大战

};

