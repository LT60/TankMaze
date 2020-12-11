#pragma once
//CGame�����������Ϸ������
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
	//��������Ӧ���ܣ�
	void SetHandle(HWND hWnd);					//����������ڵľ��
	bool EnterFrame(DWORD dwTime);				//������Ϸ֡
	void OnMouseMove(UINT nFlags, CPoint point);//��������ƶ��¼�
	void OnLButtonUp(UINT nFlags, CPoint point);//�������̧���¼�
private:
	HWND m_hWnd;								//����
	//1.5.3��Ϸ��ͼ����
	//����滭��Ϸ�еĶ�����Ϸ���еĻ�ͼ�������ᾭ������ַ���
	void GameRunDraw();
	/* ��Ϸ�߼�����
	 * 1. ά���ӵ�״̬
	 * 2. ά��������AI���Զ��ƶ����Զ������ӵ�
	 * 3. ά�����̹�˵�״̬
	 * ��ײ��������׬Ǯ���ӵ�����̹��
	 */
	void GameRunLogic();
	//1.6�����˵���ĳ�Ա����
	//CGameMenuPanel m_menuSelect;//��ʼ�˵�//����������������������������
	CGameMenuBackground m_menu;//����

	//���fps
	void Drawfps(Graphics& gh);
	//��¼֡��
	int m_fps{ 0 };

	CPlayer m_player01{ 100, 100, _T("tank_player1.png") }; // ��Ҷ���

	CPlayer m_player02{ 200, 100, _T("tank_player2.png") }; // ��Ҷ���2: ˫�˶�սʱ�Ż��õ�

	CBot m_bot{ 300, 200, _T("tank_bot.png") };             // һ������: �˻���սʱ�õ�

	std::list<CBullet> m_lstBullets;                        // �����ڵ�ͼ�����е� �ӵ���������

};
