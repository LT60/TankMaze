#pragma once
#include"CGameMenuBackground.h"
#include"CGameMenuPanel.h"
#include "TankEntry.h"
#include "Player.h"
#include "Bullet.h"
#include "Bot.h"
#include "GameMap.h"

//������Ϸ
//����������MainFrm.h

class CGame
{
public:
    CGame();
    ~CGame();

    void SetHandle(HWND hWnd);		// ����������ڵľ��

    bool EnterFrame(DWORD dwTime); 	// ������Ϸ֡

    void OnMouseMove(UINT nFlags, CPoint point); // ��������ƶ��¼�

    void OnLButtonUp(UINT nFlags, CPoint point); // �������̧���¼�

//private:
public:
    HWND m_hWnd; // ����

    //��Ϸ��ͼ����
    //���� �滭 ��Ϸ�еĶ���
    void GameRunDraw();
    void GameRunLogic();

    CGameMenuPanel m_menuSelect;
    CGameMenuBackground m_menu;

    // ���fps
    void DrawFps(Graphics& gh);

    // ��¼ ��Ϸÿ�����֡
    int m_fps{ 0 };

    CPlayer m_player01{ 100, 100, _T("tank_player1.png") }; // ������Ҷ���

    CPlayer m_player02{ 200, 100, _T("tank_player2.png") }; // ��Ҷ���2: ˫�˶�սʱ�Ż��õ�

    CBot m_bot{ 300, 200, _T("tank_bot.png") };              // һ������: �˻���սʱ�õ�

    std::list<CBullet> m_lstBullets;                        // �����ڵ�ͼ�����е� �ӵ���������

    CGameMap m_map{ 10, 10, 780, 580 };             //��ͼ����

    bool CGame::GameInitOne2Bot(); //��Ϸ��ʼ�����˻���ս

};

