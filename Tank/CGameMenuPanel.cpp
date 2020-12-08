#include "pch.h"
#include "CGameMenuPanel.h"
#include "CGame.h"
// 构造函数
CGameMenuPanel::CGameMenuPanel()
{
    // 背景图
    m_imgBackground = Image::FromFile(_T("menu_background.png"));       //？？不应该是给background类画吗？怎么给panel画了

    // 菜单项一 : 人机对战
    m_menuItems[0].index = 0;
    for (int i = 0; i < 2; ++i) {
        TCHAR path[MAX_PATH];
        _stprintf_s(path, _T("menu_1player_%d.png"), i);               // 格式化文件名
        auto imgPtr = Image::FromFile(path);                            // 载入图片
        RectF rc(0, 300, static_cast<float>(imgPtr->GetWidth()),
            static_cast<float>(imgPtr->GetHeight()));
        m_menuItems[0].vImgInfoPtr.push_back(make_tuple(imgPtr, rc)); // 图片存在数组中
    }

    // 菜单项一 : 双人对战
    m_menuItems[1].index = 0;
    for (int i = 0; i < 2; ++i) {
        TCHAR path[MAX_PATH];
        _stprintf_s(path, _T("menu_2plyaer_%d.png"), i);              // 格式化文件名
        auto imgPtr = Image::FromFile(path);                           // 载入图片
        RectF rc(400, 300, static_cast<float>(imgPtr->GetWidth())
            , static_cast<float>(imgPtr->GetHeight()));
        m_menuItems[1].vImgInfoPtr.push_back(make_tuple(imgPtr, rc)); // 图片存在数组中
    }
}

CGameMenuPanel::~CGameMenuPanel()                                        // 析构函数
{

}

// 绘制自己
void CGameMenuPanel::Draw(Graphics& gh) const
{
    gh.DrawImage(m_imgBackground, m_rect);                              // 画出背景图片

    // 画子菜单
    for (auto menuItem : m_menuItems) {
        auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);      // 获取菜单项的图片
        auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);     // 获取菜单项的大小
        gh.DrawImage(img, rect);
    }
}

// 处理 鼠标移动事件
void CGameMenuPanel::OnMouseMove(UINT nFlags, CPoint point)
{
    PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
    // 画子菜单
    for (auto& menuItem : m_menuItems) {
        auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]); // 获取菜单项的图片
        auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);// 获取菜单项的大小
        if (rect.Contains(pt)) {                                     // 判断是否包含当前鼠标位置
            menuItem.index = 1;                                     // 包含：显示第1张图片                                       
        }
        else {
            menuItem.index = 0;                                     // 不包含：显示第0张图片
        }
    }
}

// 处理 鼠标左键抬起事件
void CGameMenuPanel::OnLButtonUp(UINT nFlags, CPoint point)
{
    PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
    {
        auto& menuItem = m_menuItems[0];							// 获取第0张图片
        auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);	// 获取图片指针
        auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);	// 获取图片大小
        if (rect.Contains(pt)) {									// 判断是否点中图片
            // 人机对战：暂时不设置
            // m_pParent->SetStep(CGame::EGameTypeOne2BotMenu);
            return;
        }
    }
    {
        auto& menuItem = m_menuItems[1];							// 获取第0张图片
        auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);	// 获取图片指针
        auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);	// 获取图片大小
        if (rect.Contains(pt)) {									// 判断是否点中图片
            // 双人对战：暂时不设置
            //m_pParent->SetStep(CGame::EGameTypeOne2OneMenu);
            return;
        }
    }
}
