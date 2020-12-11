#include "pch.h"
#include "CGame.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::SetHandle(HWND hWnd)  					// ����������ڵľ��
{
    m_hWnd = hWnd;
}

bool CGame::EnterFrame(DWORD dwTime)				// ������Ϸ֡
{
    GameRunDraw();
    return false;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point) // ��������ƶ��¼�
{
    m_menuSelect.OnMouseMove(nFlags, point);//  ѡ����Ϸ����
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point) // �������̧���¼�
{
    m_menuSelect.OnLButtonUp(nFlags, point);
}
// ��Ϸ��ͼ
void CGame::GameRunDraw()
{
    HDC hdc = ::GetDC(m_hWnd);
    CRect rc; 									// �ͻ����Ĵ�С
    GetClientRect(m_hWnd, &rc);

    CDC* dc = CClientDC::FromHandle(hdc);

    CDC m_dcMemory; 								// ˫�����ͼ��
    CBitmap bmp;
    bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
    m_dcMemory.CreateCompatibleDC(dc);
    CBitmap* pOldBitmap = m_dcMemory.SelectObject(&bmp);

    Graphics gh(m_dcMemory.GetSafeHdc());			// �������
    gh.Clear(Color::White); 						// �������
    gh.ResetClip();

    m_menu.Draw(gh);
    m_menuSelect.Draw(gh);
    DrawFps(gh); 									// �����ڴ�

    ::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),	// ��������Ļ
        m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
    dc->DeleteDC();								// �ͷ�
    return;
}

// �� fps
void CGame::DrawFps(Graphics& gh)
{
    static int fps = 0;							// ���徲̬������ÿ�ν��뺯��ʱ�����ϴε�ֵ
    m_fps++;                                           // ��¼�������˶���֡
    static DWORD dwLast = GetTickCount();           // ��¼�ϴ����fps��ʱ��
    if (GetTickCount() - dwLast >= 1000) {           // ����ʱ���Ƿ񳬹� 1�룬������������ fps
        fps = m_fps;
        m_fps = 0;                                    // ���㣬�����֡�������¼���
        dwLast = GetTickCount();                     // ��¼���������ʱ��
    }

    // ���fps
    {
        CString s;
        s.Format(_T("FPS:%d"), fps);                // ��fsp ��ʽ���� �ַ���
        SolidBrush brush(Color(0x00, 0x00, 0xFF)); // ������ɫ�Ļ�ˢ
        Gdiplus::Font font(_T("����"), 10.0);       // �������������
        CRect rc;
        ::GetClientRect(m_hWnd, &rc);             // ���������ڵĴ�С��������λ���ֵ����λ��
        PointF origin(static_cast<float>(rc.right - 70),          // �����Ͻ���ʾ
            static_cast<float>(rc.top + 2));
        gh.DrawString(s.GetString(), -1, &font, origin, &brush); // ��ʽ������
    }
}
