#pragma once

class CGameMenuBackground
{
public:
	CGameMenuBackground();

	void Draw(Graphics& gh) const;

	RectF m_rect{ 0,0,800,600 };
	Image* m_imgBackground;
};

