#pragma once
#include"CGameMenuBackground.h"
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
    CGameMenuBackground m_menu;

    // ���fps
    void DrawFps(Graphics& gh);

    // ��¼ ��Ϸÿ�����֡
    int m_fps{ 0 };

};

