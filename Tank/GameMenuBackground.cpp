#include "pch.h"
#include "GameMenuBackground.h"
#include "CGame.h"


CGameMenuBackground::CGameMenuBackground()
{
    m_imgBackground = Image::FromFile(_T("menu_background.png")); 	    //构造函数直接载入背景图
}

CGameMenuBackground::~CGameMenuBackground()
{

}

void CGameMenuBackground::Draw(Graphics& gh) const
{
    gh.DrawImage(m_imgBackground, m_rect);                          	// 直接画：绘制自己（背景图片）
}
