#pragma once

#include <tuple>
#include <vector>
#include "GameEntry.h"

using namespace std;

class CGame;

class CGameMenuPanel : public CGameEntryMoveable
{
public:
    CGameMenuPanel();
    ~CGameMenuPanel();

    // 存放一个CGame类的指针在本中
    void SetParent(CGame* g)
    {
        m_pParent = g;
    };

    CGame* m_pParent{ nullptr };                    // 存放一个CGame类的指针在本中
        
    virtual void Draw(Graphics& gh) const;          // 画自己

    RectF m_rect{ 0, 0, 800, 600 };                 // 自己的范围

    void OnMouseMove(UINT nFlags, CPoint point);    // 处理 鼠标 移动 事件

    void OnLButtonUp(UINT nFlags, CPoint point);    // 处理 鼠标 左键抬起 事件

    Image* m_imgBackground;                         // 背景图

    struct 
    {                                               // 菜单项
        vector<tuple<Image*, RectF>> vImgInfoPtr;   //图片相关信息（指针和范围）
        int index;                                  //下标
    } m_menuItems[2];
};
