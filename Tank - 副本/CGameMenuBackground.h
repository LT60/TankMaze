#pragma once

#include "GameEntry.h"

class CGame;

class CGameMenuBackground : public CGameEntryMoveable   //也是可移动对象？？？？？
{
public:
    CGameMenuBackground();
    ~CGameMenuBackground();

    void SetParent(CGame* g)
    {
        m_pParent = g;
    };

    CGame* m_pParent{ nullptr };

    virtual void Draw(Graphics& gh) const; 		//画自己的函数

    RectF m_rect{ 0, 0, 800, 600 };           	//自己的范围

    Image* m_imgBackground;                  	//保存图片的指针
};
