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

	//把设备句柄转换成cdc对象
	CDC* dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory;				//双缓冲绘图用
	CBitmap bmp;				//内存中的绘图对象
	//创建这个对象
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	//在内存中创建合适的图像，传入游戏窗口设备句柄
	m_dcMemory.CreateCompatibleDC(dc);
	//选中这个绘图
	CBitmap* poldBitmap = m_dcMemory.SelectObject(&bmp);

	//正式使用gdi+对象
	Graphics gh(m_dcMemory.GetSafeHdc());	//构造对象
	gh.Clear(Color::White);					//清除背景
	gh.ResetClip();							//重新设置
	
	//绘制：

	/*//画背景图片
	{
		//获取游戏窗口大小
		CRect rc;
		GetClientRect(m_hWnd, rc);
		
		//载入要绘制的图片
		Gdiplus::Image* img = Image::FromFile(_T("menu_background.png"));

		//画
		gh.DrawImage(img, rc.left, rc.top, rc.Width(), rc.Height());
	}

	Drawfps(gh);							//画入内存
	*/

	//把内存当中的图片拷贝到屏幕上
	//（拷贝位置是0，0，大小也是客户区大小，从内存当中进行拷贝，拷贝位置也是0，0，拷贝方式是直接复制）
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),//复制到屏幕
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	dc->DeleteDC();								//随后释放

	return;
}

//画fps
void CGame::Drawfps(Graphics& gh)
{
	//定义静态变量，每次进入函数时保存上次的值
	static int fps = 0;	//记录Drawfps调用了多少次	

	//记录已经画了多少帧
	m_fps++;				

	//记录上次输出fps的时间
	static DWORD dwLast = GetTickCount();

	//判断时间是否超过1秒，如果超过，输出fps
	if (GetTickCount() - dwLast >= 1000)
	{
		fps = m_fps;
		m_fps = 0;		//复位
		dwLast = GetTickCount();//记录本次输出的时间
	}

	//输出fps
	{
		CString s;
		s.Format(_T("FPS:%d"), fps);//将fps格式化到字符串
		//创建红色的画刷
		SolidBrush brush(Color(0x00, 0x00, 0xFF));
		//创建输出的字体
		Gdiplus::Font font(_T("宋体"),5.0);
		CRect rc;
		//获取输出窗口的大小，用来定位文字的输出位置
		::GetClientRect(m_hWnd, &rc);
		//在右上角显示（距离右边是50，距离上边是2）
		//把整数转换成浮点型以适应参数
		PointF origin(static_cast<float>(rc.right - 50), static_cast<float>(rc.top + 2));
		//输出
		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}


