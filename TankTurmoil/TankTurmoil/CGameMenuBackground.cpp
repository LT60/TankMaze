#include "pch.h"
#include "CGameMenuBackground.h"

CGameMenuBackground::CGameMenuBackground()
{
	m_imgBackground = Image::FromFile(_T("D:\\menu_background.png"));
}
void CGameMenuBackground::Draw(Graphics& gh) const
{
	gh.DrawImage(m_imgBackground, m_rect);
}