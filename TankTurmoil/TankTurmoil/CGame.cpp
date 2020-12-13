#include "pch.h"
#include "CGame.h"
#include <algorithm>

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::SetHandle(HWND hWnd)  					// 设置输出窗口的句柄
{
    m_hWnd = hWnd;
}

bool CGame::EnterFrame(DWORD dwTime)				// 进入游戏帧
{
    GameRunDraw();
    GameRunLogic();
    return false;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point) // 处理鼠标移动事件
{
    m_menuSelect.OnMouseMove(nFlags, point);//  选择游戏类型
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point) // 处理左键抬起事件
{
    m_menuSelect.OnLButtonUp(nFlags, point);
}
// 游戏绘图
void CGame::GameRunDraw()
{
    HDC hdc = ::GetDC(m_hWnd);
    CRect rc; 									// 客户区的大小
    GetClientRect(m_hWnd, &rc);

    CDC* dc = CClientDC::FromHandle(hdc);

    CDC m_dcMemory; 								// 双缓冲绘图用
    CBitmap bmp;
    bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
    m_dcMemory.CreateCompatibleDC(dc);
    CBitmap* pOldBitmap = m_dcMemory.SelectObject(&bmp);

    Graphics gh(m_dcMemory.GetSafeHdc());			// 构造对象
    gh.Clear(Color::White); 						// 清除背景
    gh.ResetClip();

    //m_menu.Draw(gh);
    //m_menuSelect.Draw(gh);
    // 画入内存
    //{
    //    m_player01.Draw(gh);             			// 画坦克(玩家一)
    //    for (auto& blt : m_lstBullets) { 			// 遍历所有存在于地图上的子弹
    //        blt.Draw(gh);							// 调用子弹自身绘制函数，绘制子弹
    //    }
    //}
    m_map.Draw(gh); 					// 画出地图
    m_player01.Draw(gh); 				// 画坦克(玩家一)
    for (auto& blt : m_lstBullets) {	// 画子弹(所有存在于地图上的子弹)
        blt.Draw(gh);
    }

    DrawFps(gh); 									// 画入内存

    ::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),	// 拷贝到屏幕
        m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
    dc->DeleteDC();								// 释放
    return;
}

// 画 fps
void CGame::DrawFps(Graphics& gh)
{
    static int fps = 0;							// 定义静态变量，每次进入函数时保存上次的值
    m_fps++;                                           // 记录己经画了多少帧
    static DWORD dwLast = GetTickCount();           // 记录上次输出fps的时间
    if (GetTickCount() - dwLast >= 1000) {           // 判数时间是否超过 1秒，如果超过，输出 fps
        fps = m_fps;
        m_fps = 0;                                    // 清零，方便对帧进行重新记数
        dwLast = GetTickCount();                     // 记录本次输出的时间
    }

    // 输出fps
    {
        CString s;
        s.Format(_T("FPS:%d"), fps);                // 将fsp 格式化到 字符串
        SolidBrush brush(Color(0x00, 0x00, 0xFF)); // 创建红色的画刷
        Gdiplus::Font font(_T("宋体"), 10.0);       // 创建输出的字体
        CRect rc;
        ::GetClientRect(m_hWnd, &rc);             // 获得输出窗口的大小，用来定位文字的输出位置
        PointF origin(static_cast<float>(rc.right - 80),          // 在右上角显示
            static_cast<float>(rc.top + 2));
        gh.DrawString(s.GetString(), -1, &font, origin, &brush); // 正式出文字
    }
}

void CGame::GameRunLogic()
{
#define KEYDOWN(vk) (GetAsyncKeyState(vk) & 0x8000)
    //按键处理
    {
        if (KEYDOWN(VK_LEFT))          // 左方向盘按下
        {
            m_player01.RotateLeft(); // 玩家一向左转
        }
        if (KEYDOWN(VK_RIGHT))          			// 右方向盘按下
        {
            m_player01.RotateRight();			// 玩家一向右转
        }
        if (KEYDOWN(VK_UP))            			// 上方向盘按下
        {
            m_player01.Forward();     			// 玩家一向前走
        }
        if (KEYDOWN(VK_DOWN))          			// 下方向盘按下
        {
            {
                m_player01.Backward(); 		// 玩家一向后退
            }
        }
        if (KEYDOWN('M'))                		// 按下M键
        {
            CBullet blt;
            if (m_player01.Fire(blt)) {        	// 开火
                m_lstBullets.push_back(blt); 	// 加入到地图列表中
            }
        }
    }

    for (auto& blt : m_lstBullets) {          	// 处理子弹对象的移动
        blt.Move();                            	// 子弹向前移动
    }

    // 移除超时的子弹
    {
        // 查找超时的子弹
        auto itRemove = std::remove_if(m_lstBullets.begin(),
            m_lstBullets.end(),
            [](CBullet& blt)->bool {
                return blt.IsTimeout();
            });
        for (auto it = itRemove; it != m_lstBullets.end(); ++it) {
            it->SetActive(false);				// 设置为无效
            it->GetOwner()->AddBullet(*it);	// 给对应的坦克增加子弹
        }
        // 从本地 删除 子弹
        m_lstBullets.erase(itRemove, m_lstBullets.end());
    }
}
