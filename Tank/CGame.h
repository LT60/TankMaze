#pragma once
//CGame�����������Ϸ������
class CGame
{

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
	//���fps
	void Drawfps(Graphics& gh);
	//��¼֡��
	int m_fps{ 0 };
};
