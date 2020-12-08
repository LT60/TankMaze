#include "pch.h"
#include "CGame.h"

void CGame::SetHandle(HWND hWnd)
{
	m_hWnd = hWnd;
}

bool CGame::EnterFrame(DWORD dwTime)
{
	//����
	GameRunDraw();
	return false;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
}
//ÿ�ν�����Ϸ֡������
void CGame::GameRunDraw()
{
	//�������ܣ������ڴ��д���һ��ͼƬ��Ȼ�����DrawFps��������Ϸ֡����ͼƬ�ϣ����Ѹ��ڴ��е�ͼƬһ���Ը��Ƶ���Ϸ������
	HDC hdc = ::GetDC(m_hWnd);	//�ͻ����Ĵ�С
	CRect rc;
	GetClientRect(m_hWnd, &rc);

	//���豸���ת����cdc����
	CDC* dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory;				//˫�����ͼ��
	CBitmap bmp;				//�ڴ��еĻ�ͼ����
	//�����������
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	//���ڴ��д������ʵ�ͼ�񣬴�����Ϸ�����豸���
	m_dcMemory.CreateCompatibleDC(dc);
	//ѡ�������ͼ
	CBitmap* poldBitmap = m_dcMemory.SelectObject(&bmp);

	//��ʽʹ��gdi+����
	Graphics gh(m_dcMemory.GetSafeHdc());	//�������
	gh.Clear(Color::White);					//�������
	gh.ResetClip();							//��������
	
	//���ƣ�

	/*//������ͼƬ
	{
		//��ȡ��Ϸ���ڴ�С
		CRect rc;
		GetClientRect(m_hWnd, rc);
		
		//����Ҫ���Ƶ�ͼƬ
		Gdiplus::Image* img = Image::FromFile(_T("menu_background.png"));

		//��
		gh.DrawImage(img, rc.left, rc.top, rc.Width(), rc.Height());
	}

	Drawfps(gh);							//�����ڴ�
	*/

	//���ڴ浱�е�ͼƬ��������Ļ��
	//������λ����0��0����СҲ�ǿͻ�����С�����ڴ浱�н��п���������λ��Ҳ��0��0��������ʽ��ֱ�Ӹ��ƣ�
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),//���Ƶ���Ļ
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	dc->DeleteDC();								//����ͷ�

	return;
}

//��fps
void CGame::Drawfps(Graphics& gh)
{
	//���徲̬������ÿ�ν��뺯��ʱ�����ϴε�ֵ
	static int fps = 0;	//��¼Drawfps�����˶��ٴ�	

	//��¼�Ѿ����˶���֡
	m_fps++;				

	//��¼�ϴ����fps��ʱ��
	static DWORD dwLast = GetTickCount();

	//�ж�ʱ���Ƿ񳬹�1�룬������������fps
	if (GetTickCount() - dwLast >= 1000)
	{
		fps = m_fps;
		m_fps = 0;		//��λ
		dwLast = GetTickCount();//��¼���������ʱ��
	}

	//���fps
	{
		CString s;
		s.Format(_T("FPS:%d"), fps);//��fps��ʽ�����ַ���
		//������ɫ�Ļ�ˢ
		SolidBrush brush(Color(0x00, 0x00, 0xFF));
		//�������������
		Gdiplus::Font font(_T("����"),5.0);
		CRect rc;
		//��ȡ������ڵĴ�С��������λ���ֵ����λ��
		::GetClientRect(m_hWnd, &rc);
		//�����Ͻ���ʾ�������ұ���50�������ϱ���2��
		//������ת���ɸ���������Ӧ����
		PointF origin(static_cast<float>(rc.right - 50), static_cast<float>(rc.top + 2));
		//���
		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}


