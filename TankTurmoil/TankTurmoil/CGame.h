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

    // ����������ڵľ��
    void SetHandle(HWND hWnd);

    // ������Ϸ֡
    bool EnterFrame(DWORD dwTime);

    // ��������ƶ��¼�
    void OnMouseMove(UINT nFlags, CPoint point);

    // �������̧���¼�
    void OnLButtonUp(UINT nFlags, CPoint point);

    // ��ǰ��Ϸ�����Ľ׶�
    enum EGameType {
        EGameTypeMenu = 0,		// ѡ��׶�
        EGameTypeOne2BotMenu,	// ���˶Ե��� �˵��׶�
        EGameTypeOne2Bot,		// ���˶Ե���
        EGameTypeOne2BotEnd,		// ���˶Ե��� ����
        EGameTypeOne2OneMenu,	// ˫�˶�ս �˵��׶�
        EGameTypeOne2One,		// ˫�˶�ս
        EGameTypeOne2OneEnd,		// ˫�˶�ս ����
        EGameTypeCount,			// = 5
    };

    // ���õ�ǰ��Ϸ�����Ľ׶�,�����ݲ��� ��ʼ��
    void SetStep(CGame::EGameType step);

private:
    // ����
    HWND m_hWnd;

    /* ��Ϸ��ʼ��
    ���� ��Ϸ���󣬳�ʼ����ͼ������λ�õ�
    */
    bool GameInit();

    bool GameInitMenu();				// ��Ϸ��ʼ�� : ѡ��׶�

    bool GameInitOne2BotMenu(); 		// ��Ϸ��ʼ�� : ���˶Ե��� �˵��׶�

    bool GameInitOne2Bot();			// ��Ϸ��ʼ�� : ���˶Ե���

    bool GameInitOne2BotEnd();		// ��Ϸ��ʼ�� : ���˶Ե��� ����

    bool GameInitOne2OneMenu();		// ��Ϸ��ʼ�� : ˫�˶�ս �˵��׶�

    bool GameInitOne2One();			// ��Ϸ��ʼ�� : ˫�˶�ս

    bool GameInitOne2OneEnd();		// ��Ϸ��ʼ�� : ˫�˶�ս ����

    // �����������������飬�������
    bool (CGame::* m_initFunc[EGameTypeCount])() = {
        &CGame::GameInitMenu,        	// ѡ��׶�
        &CGame::GameInitOne2BotMenu, 	// ���˶Ե��Լ�����ʾ
        &CGame::GameInitOne2Bot,     	// ���˶Ե���
        &CGame::GameInitOne2BotEnd,  	// ���˶Ե��� ����
        &CGame::GameInitOne2OneMenu, 	// ˫�˶�ս������ʾ
        &CGame::GameInitOne2One,      	// ˫�˶�ս
        &CGame::GameInitOne2OneEnd   	// ˫�˶�ս ����
    };

    /* ��Ϸ�߼�����:
    1. ά���ӵ�״̬
    2. ά�� ������AI���Զ��ƶ�,�Զ������ӵ�
    3. ά�� ��� ̹�˵�״̬
    �Բ�������� ײǽ���ӵ�����̹��...*/
    void GameRunLogic();

    void GameRunLogicOnMenu();				// ��Ϸ�߼����� : ѡ��׶�

    void GameRunLogicOnOne2BotMenu();			// ��Ϸ�߼����� : ���˶Ե��� �˵��׶�

    void GameRunLogicOnOne2Bot();				// ��Ϸ�߼����� : ���˶Ե���

    void GameRunLogicOnOne2BotEnd();			// ��Ϸ�߼����� : ���˶Ե��� ����

    void GameRunLogicOnOne2OneMenu();			// ��Ϸ�߼����� : ˫�˶�ս �˵��׶�

    void GameRunLogicOnOne2One();				// ��Ϸ�߼����� : ˫�˶�ս

    void GameRunLogicOnOne2OneEnd();			// ��Ϸ�߼����� : ˫�˶�ս ����

    // �����������������飬�������
    void(CGame::* m_logicFunc[EGameTypeCount])() = {
        &CGame::GameRunLogicOnMenu,         	// ѡ��׶�
        &CGame::GameRunLogicOnOne2BotMenu, 	// �˻���ս������ʾ
        &CGame::GameRunLogicOnOne2Bot,      	// ���˶Ե���
        &CGame::GameRunLogicOnOne2BotEnd,   	// ���˶Ե��� ����
        &CGame::GameRunLogicOnOne2OneMenu,  	// ˫�˶�ս������ʾ
        &CGame::GameRunLogicOnOne2One,      	// ˫�˶�ս
        &CGame::GameRunLogicOnOne2OneEnd    	// ˫�˶�ս ����
    };

    /* ��Ϸ��ͼ����
    ���� �滭 ��Ϸ�еĶ���
    */
    void GameRunDraw();

    void GameRunDrawOnMenu(Graphics& gh); 		// ��Ϸ��ͼ���� : ѡ��׶�

    void GameRunDrawOnOne2BotMenu(Graphics& gh); 	// ��Ϸ��ͼ���� : ���˶Ե��� �˵��׶�

    void GameRunDrawOnOne2Bot(Graphics& gh); 		// ��Ϸ��ͼ���� : ���˶Ե���

    void GameRunDrawOnOne2BotEnd(Graphics& gh); 	// ��Ϸ��ͼ���� : ���˶Ե��� ����

    void GameRunDrawOnOne2OneMenu(Graphics& gh); 	// ��Ϸ��ͼ���� : ˫�˶�ս �˵��׶�

    void GameRunDrawOnOne2One(Graphics& gh); 		// ��Ϸ��ͼ���� : ˫�˶�ս

    void GameRunDrawOnOne2OneEnd(Graphics& gh); 	// ��Ϸ��ͼ���� : ˫�˶�ս ����

    // �����������������飬�������
    void(CGame::* m_drawFunc[EGameTypeCount])(Graphics&) = {
        &CGame::GameRunDrawOnMenu, 				// ѡ��׶�
        &CGame::GameRunDrawOnOne2BotMenu, 		// �˻���ս�׶�
        &CGame::GameRunDrawOnOne2Bot, 			// ���˶Ե���
        &CGame::GameRunDrawOnOne2BotEnd, 			// ���˶Ե��� ����
        &CGame::GameRunDrawOnOne2OneMenu, 		// ˫�˶�ս�׶�
        &CGame::GameRunDrawOnOne2One, 			// ˫�˶�ս
        &CGame::GameRunDrawOnOne2OneEnd 			// ˫�˶�ս ����
    };

private://��������

    void RemoveTimeoutBullets();				// �Ƴ���ʱ�ӵ�,������Ӧ��̹��װ��

    void ProcessHitBullets();					// ά���ӵ������У���ײǽ����

    void AI();								// ά�����Ե��Զ�Ѱ·����

    void DrawFps(Graphics& gh); 				// ���fps

private:
    int m_fps{ 0 }; 						// ��¼ ��Ϸÿ�����֡

    EGameType m_eStep{ EGameTypeMenu }; 	// ��ǰ�׶�:�˵�ѡ��׶�

    CPlayer m_player01; 					// ������Ҷ���

    CPlayer m_player02; 					// ��Ҷ���2: ˫�˶�սʱ�Ż��õ�

    CBot m_bot; 							// һ������: �˻���սʱ�õ�

    std::list<CBullet> m_lstBullets; 		// �����ڵ�ͼ�����е� �ӵ���������

    CGameMap m_map{ 10, 10, 1180, 880 }; 	// ��ͼ����

    CGameMenuPanel m_menuSelect; 			// ��ʼ�˵�

    CGameMenuBackground m_menu; 			// ��ʼ�˵�����ͼ

    CGameMenuPanel2 m_menuBackup; 			// ���ز˵�

    CKeyMenuPlayer01 m_keymenu01; 			// ��ʾ�����Ĳ˵�
    CKeyMenuPlayer02 m_keymenu02;
};  // ע�⣺�˴��зֺ�
