#include "pch.h"
#include "CGame.h"

void CGame::SetHandle(HWND hWnd)
{
	m_hWnd = hWnd;
}

bool CGame::EnterFrame(DWORD dwTime)
{
	//调用
	GameRunDraw();
	return false;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
}
//每次进入游戏帧都调用
void CGame::GameRunDraw()
{
	//函数功能：先在内存中创建一张图片，然后调用DrawFps函数把游戏帧画在图片上，最后把该内存中的图片一次性复制到游戏窗口中
	HDC hdc = ::GetDC(m_hWnd);	//客户区的大小
	CRect rc;
	GetClientRect(m_hWnd, &rc);

	CDC* dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory;				//双缓冲绘图用
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap* poldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());	//构造对象
	gh.Clear(Color::White);					//清除背景
	gh.ResetClip();
	
	Drawfps(gh);							//画入内存

	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),//复制到屏幕
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	dc->DeleteDC();							//释放

	return;
}

//画fps
void CGame::Drawfps(Graphics& gh)
{
	//定义静态变量，每次进入函数时保存上次的值
	static int fps = 0;		

	//记录已经画了多少帧
	m_fps++;				

	//记录上次输出fps的时间
	static DWORD dwLast = GetTickCount();

	//判断时间是否超过1秒，如果超过，输出fps
	if (GetTickCount64() - dwLast >= 1000)
	{
		fps = m_fps;
		m_fps = 0;		//复位
		dwLast = GetTickCount64();//记录本次输出的时间
	}

	//输出fps
	{
		CString s;
		s.Format(_T("FPS:%d"), fps);//将fps格式化到字符串
		SolidBrush brush(Color(0x00, 0x00, 0xFF));//创建红色的画刷
		Gdiplus::Font font(_T("宋体"),5.0);//创建输出的字体
		CRect rc;
		//获取输出窗口的大小，用来定位文字的输出位置
		::GetClientRect(m_hWnd, &rc);
		//在右上角显示：
		PointF origin(static_cast<float>(rc.right - 50), static_cast<float>(rc.top + 2));
		//输出
		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}


