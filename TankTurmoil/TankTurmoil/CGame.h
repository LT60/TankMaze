#pragma once

#include "wall.h"
#include "Bullet.h"
#include "Player.h"
#include "Bot.h"
#include "GameMap.h"
#include "CGameMenuPanel.h"
#include "GameMenuPanel2.h"
#include "KeyMenuPlayer02.h"
#include "KeyMenuPlayer01.h"
#include "CGameMenuBackground.h"


class CGame
{
public:
    CGame();
    ~CGame();

    // 设置输出窗口的句柄
    void SetHandle(HWND hWnd);

    // 进入游戏帧
    bool EnterFrame(DWORD dwTime);

    // 处理鼠标移动事件
    void OnMouseMove(UINT nFlags, CPoint point);

    // 处理左键抬起事件
    void OnLButtonUp(UINT nFlags, CPoint point);

    // 当前游戏所处的阶段
    enum EGameType {
        EGameTypeMenu = 0,		// 选择阶段
        EGameTypeOne2BotMenu,	// 单人对电脑 菜单阶段
        EGameTypeOne2Bot,		// 单人对电脑
        EGameTypeOne2BotEnd,		// 单人对电脑 结束
        EGameTypeOne2OneMenu,	// 双人对战 菜单阶段
        EGameTypeOne2One,		// 双人对战
        EGameTypeOne2OneEnd,		// 双人对战 结束
        EGameTypeCount,			// = 5
    };

    // 设置当前游戏所处的阶段,并根据步聚 初始化
    void SetStep(CGame::EGameType step);

private:
    // 窗口
    HWND m_hWnd;

    /* 游戏初始化
    生成 游戏对象，初始化地图，对象位置等
    */
    bool GameInit();

    bool GameInitMenu();				// 游戏初始化 : 选择阶段

    bool GameInitOne2BotMenu(); 		// 游戏初始化 : 单人对电脑 菜单阶段

    bool GameInitOne2Bot();			// 游戏初始化 : 单人对电脑

    bool GameInitOne2BotEnd();		// 游戏初始化 : 单人对电脑 结束

    bool GameInitOne2OneMenu();		// 游戏初始化 : 双人对战 菜单阶段

    bool GameInitOne2One();			// 游戏初始化 : 双人对战

    bool GameInitOne2OneEnd();		// 游戏初始化 : 双人对战 结束

    // 把上述方法放入数组，方便调用
    bool (CGame::* m_initFunc[EGameTypeCount])() = {
        &CGame::GameInitMenu,        	// 选择阶段
        &CGame::GameInitOne2BotMenu, 	// 单人对电脑键盘提示
        &CGame::GameInitOne2Bot,     	// 单人对电脑
        &CGame::GameInitOne2BotEnd,  	// 单人对电脑 结束
        &CGame::GameInitOne2OneMenu, 	// 双人对战键盘提示
        &CGame::GameInitOne2One,      	// 双人对战
        &CGame::GameInitOne2OneEnd   	// 双人对战 结束
    };

    /* 游戏逻辑处理:
    1. 维护子弹状态
    2. 维护 机器人AI的自动移动,自动发射子弹
    3. 维护 玩家 坦克的状态
    以测检测包括： 撞墙，子弹命中坦克...*/
    void GameRunLogic();

    void GameRunLogicOnMenu();				// 游戏逻辑处理 : 选择阶段

    void GameRunLogicOnOne2BotMenu();			// 游戏逻辑处理 : 单人对电脑 菜单阶段

    void GameRunLogicOnOne2Bot();				// 游戏逻辑处理 : 单人对电脑

    void GameRunLogicOnOne2BotEnd();			// 游戏逻辑处理 : 单人对电脑 结束

    void GameRunLogicOnOne2OneMenu();			// 游戏逻辑处理 : 双人对战 菜单阶段

    void GameRunLogicOnOne2One();				// 游戏逻辑处理 : 双人对战

    void GameRunLogicOnOne2OneEnd();			// 游戏逻辑处理 : 双人对战 结束

    // 把上述方法放入数组，方便调用
    void(CGame::* m_logicFunc[EGameTypeCount])() = {
        &CGame::GameRunLogicOnMenu,         	// 选择阶段
        &CGame::GameRunLogicOnOne2BotMenu, 	// 人机对战按键提示
        &CGame::GameRunLogicOnOne2Bot,      	// 单人对电脑
        &CGame::GameRunLogicOnOne2BotEnd,   	// 单人对电脑 结束
        &CGame::GameRunLogicOnOne2OneMenu,  	// 双人对战按键提示
        &CGame::GameRunLogicOnOne2One,      	// 双人对战
        &CGame::GameRunLogicOnOne2OneEnd    	// 双人对战 结束
    };

    /* 游戏绘图处理
    负责 绘画 游戏中的对象
    */
    void GameRunDraw();

    void GameRunDrawOnMenu(Graphics& gh); 		// 游戏绘图处理 : 选择阶段

    void GameRunDrawOnOne2BotMenu(Graphics& gh); 	// 游戏绘图处理 : 单人对电脑 菜单阶段

    void GameRunDrawOnOne2Bot(Graphics& gh); 		// 游戏绘图处理 : 单人对电脑

    void GameRunDrawOnOne2BotEnd(Graphics& gh); 	// 游戏绘图处理 : 单人对电脑 结束

    void GameRunDrawOnOne2OneMenu(Graphics& gh); 	// 游戏绘图处理 : 双人对战 菜单阶段

    void GameRunDrawOnOne2One(Graphics& gh); 		// 游戏绘图处理 : 双人对战

    void GameRunDrawOnOne2OneEnd(Graphics& gh); 	// 游戏绘图处理 : 双人对战 结束

    // 把上述方法放入数组，方便调用
    void(CGame::* m_drawFunc[EGameTypeCount])(Graphics&) = {
        &CGame::GameRunDrawOnMenu, 				// 选择阶段
        &CGame::GameRunDrawOnOne2BotMenu, 		// 人机对战阶段
        &CGame::GameRunDrawOnOne2Bot, 			// 单人对电脑
        &CGame::GameRunDrawOnOne2BotEnd, 			// 单人对电脑 结束
        &CGame::GameRunDrawOnOne2OneMenu, 		// 双人对战阶段
        &CGame::GameRunDrawOnOne2One, 			// 双人对战
        &CGame::GameRunDrawOnOne2OneEnd 			// 双人对战 结束
    };

private://辅助方法

    void RemoveTimeoutBullets();				// 移除超时子弹,并给对应的坦克装弹

    void ProcessHitBullets();					// 维护子弹的运行，及撞墙处理

    void AI();								// 维护电脑的自动寻路攻击

    void DrawFps(Graphics& gh); 				// 输出fps

private:
    int m_fps{ 0 }; 						// 记录 游戏每秒多少帧

    EGameType m_eStep{ EGameTypeMenu }; 	// 当前阶段:菜单选择阶段

    CPlayer m_player01; 					// 两个玩家对象

    CPlayer m_player02; 					// 玩家对象2: 双人对战时才会用到

    CBot m_bot; 							// 一个电脑: 人机对战时用到

    std::list<CBullet> m_lstBullets; 		// 存在于地图场景中的 子弹对象数组

    CGameMap m_map{ 10, 10, 1180, 880 }; 	// 地图对象

    CGameMenuPanel m_menuSelect; 			// 开始菜单

    CGameMenuBackground m_menu; 			// 开始菜单背景图

    CGameMenuPanel2 m_menuBackup; 			// 返回菜单

    CKeyMenuPlayer01 m_keymenu01; 			// 提示按键的菜单
    CKeyMenuPlayer02 m_keymenu02;
};  // 注意：此处有分号
