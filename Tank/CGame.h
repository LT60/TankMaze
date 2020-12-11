#pragma once
//CGame类代表“整个游戏”对象
#include "CGameMenuBackground.h"
#include "CGameMenuPanel.h"
#include "TankEntry.h"
#include "Player.h"
#include "Bullet.h"
#include "Bot.h"


class CGame
{
public:
	CGame();
	~CGame();
public:
	//添加鼠标响应功能：
	void SetHandle(HWND hWnd);					//设置输出窗口的句柄
	bool EnterFrame(DWORD dwTime);				//进入游戏帧
	void OnMouseMove(UINT nFlags, CPoint point);//处理鼠标移动事件
	void OnLButtonUp(UINT nFlags, CPoint point);//处理左键抬起事件
private:
	HWND m_hWnd;								//窗口
	//1.5.3游戏绘图处理
	//负责绘画游戏中的对象（游戏所有的绘图操作都会经过这里分发）
	void GameRunDraw();
	/* 游戏逻辑处理：
	 * 1. 维护子弹状态
	 * 2. 维护机器人AI的自动移动，自动发射子弹
	 * 3. 维护玩家坦克的状态
	 * 碰撞检测包括：赚钱，子弹命中坦克
	 */
	void GameRunLogic();
	//1.6声明菜单类的成员变量
	//CGameMenuPanel m_menuSelect;//开始菜单//！！！！！！！！！！！！！！
	CGameMenuBackground m_menu;//背景

	//输出fps
	void Drawfps(Graphics& gh);
	//记录帧率
	int m_fps{ 0 };

	CPlayer m_player01{ 100, 100, _T("tank_player1.png") }; // 玩家对象

	CPlayer m_player02{ 200, 100, _T("tank_player2.png") }; // 玩家对象2: 双人对战时才会用到

	CBot m_bot{ 300, 200, _T("tank_bot.png") };             // 一个电脑: 人机对战时用到

	std::list<CBullet> m_lstBullets;                        // 存在于地图场景中的 子弹对象数组

};
