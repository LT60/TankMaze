#include "pch.h"
#include "GameMenuBackground.h"
#include "CGame.h"


CGameMenuBackground::CGameMenuBackground()
{
    m_imgBackground = Image::FromFile(_T("menu_background.png")); 	    //���캯��ֱ�����뱳��ͼ
}

CGameMenuBackground::~CGameMenuBackground()
{

}

void CGameMenuBackground::Draw(Graphics& gh) const
{
    gh.DrawImage(m_imgBackground, m_rect);                          	// ֱ�ӻ��������Լ�������ͼƬ��
}
