#include "pch.h"
#include "CGame.h"
#include <algorithm>

CGame::CGame()
{
    GameInitOne2Bot();//��ʼ���˻���ս
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
    GameRunLogic();
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

    //m_menu.Draw(gh);
    //m_menuSelect.Draw(gh);
    // �����ڴ�
    //{
    //    m_player01.Draw(gh);             			// ��̹��(���һ)
    //    for (auto& blt : m_lstBullets) { 			// �������д����ڵ�ͼ�ϵ��ӵ�
    //        blt.Draw(gh);							// �����ӵ�������ƺ����������ӵ�
    //    }
    //}
    m_map.Draw(gh); 					// ������ͼ
    m_player01.Draw(gh); 				// ��̹��(���һ)
    for (auto& blt : m_lstBullets) {	// ���ӵ�(���д����ڵ�ͼ�ϵ��ӵ�)
        blt.Draw(gh);
    }

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
        PointF origin(static_cast<float>(rc.right - 80),          // �����Ͻ���ʾ
            static_cast<float>(rc.top + 2));
        gh.DrawString(s.GetString(), -1, &font, origin, &brush); // ��ʽ������
    }
}

// ��Ϸ��ʼ�� : ���˶Ե���
bool CGame::GameInitOne2Bot()
{
    {
        m_map.LoadMap();// �����ͼ
        // ���һ
        {
            m_player01 = CPlayer(0, 0, _T("tank_player1.png"));
            PointF ptCenter;
            if (!m_map.FindRandomPosition(ptCenter)) {
                AfxMessageBox(_T("����Player01λ��ʧ��"));
            }
            else {
                // �������һ�����ĵ㣬�����һ���ڵ�ͼ���ӵ����м�λ��
                m_player01.SetCenterPoint(ptCenter);
            }
        }

        // �ӵ�
        m_lstBullets.clear();
    }
    return true;
}

void CGame::GameRunLogic()
{
#define KEYDOWN(vk) (GetAsyncKeyState(vk) & 0x8000)
    //��������
    {
        if (KEYDOWN(VK_LEFT))          // �����̰���
        {
            m_player01.RotateLeft(); // ���һ����ת
        }
        if (KEYDOWN(VK_RIGHT))          			// �ҷ����̰���
        {
            m_player01.RotateRight();			// ���һ����ת
        }
        if (KEYDOWN(VK_UP)) {
            // ̹��ײǽ�����
            {
                if (m_map.IsHitTheWall(m_player01, true)) {
                    m_player01.ChangeDirection(true);     // ײǽ�ˣ��ı䷽��
                }
                else {
                    m_player01.Forward();                  // û��ײǽ������ǰ��
                }
            }
        }
        if (KEYDOWN(VK_DOWN)) {
            {
                // ̹��ײǽ�����
                {
                    if (m_map.IsHitTheWall(m_player01, false)) {
                        m_player01.ChangeDirection(true);   // ײǽ�ˣ��ı䷽��
                    }
                    else {
                        m_player01.Backward();               // û��ײ������������
                    }
                }
            }
        }
        if (KEYDOWN('M'))                		// ����M��
        {
            CBullet blt;
            if (m_player01.Fire(blt)) {        	// ����
                m_lstBullets.push_back(blt); 	// ���뵽��ͼ�б���
            }
        }
    }

    for (auto& blt : m_lstBullets) {          	// �����ӵ�������ƶ�
        blt.Move();                            	// �ӵ���ǰ�ƶ�
    }

    // �Ƴ���ʱ���ӵ�
    {
        // ���ҳ�ʱ���ӵ�
        auto itRemove = std::remove_if(m_lstBullets.begin(),
            m_lstBullets.end(),
            [](CBullet& blt)->bool {
                return blt.IsTimeout();
            });
        for (auto it = itRemove; it != m_lstBullets.end(); ++it) {
            it->SetActive(false);				// ����Ϊ��Ч
            it->GetOwner()->AddBullet(*it);	// ����Ӧ��̹�������ӵ�
        }
        // �ӱ��� ɾ�� �ӵ�
        m_lstBullets.erase(itRemove, m_lstBullets.end());
    }
    // �ӵ�ײǽ����
    {
        for (auto& blt : m_lstBullets) { // �ӵ��Ƿ�ײ��ǽ : ���ײ���ˣ��ı䷽��ȵ�
            m_map.HitWallProcess(blt);  //  ����ײǽ����
            blt.Move();                   // �ӵ��ƶ�
        }
    }
    // ����ӵ��Ƿ����̹�� :  ����Ҫʹ̹�˱�ը(�ӵ��ɲ����Ƴ��ˣ���Ϊ��Ϸ��������)
    for (auto& blt : m_lstBullets) {
        if (m_player01.IsHitted(blt)) {  // ������һ������
            m_player01.Bomb();            // ʹ���һ���Ա���
        }
        break;
    }

}
