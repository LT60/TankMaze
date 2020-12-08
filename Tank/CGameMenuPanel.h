#pragma once

#include <tuple>
#include <vector>           //C++标准库中的动态数组
#include "GameEntry.h"

using namespace std;

class CGame;                //前置声明CGame类

class CGameMenuPanel : public CGameEntryMoveable    //可移动对象
{
public:
    CGameMenuPanel();
    ~CGameMenuPanel();

    // 存放一个CGame类的指针在本中
    void SetParent(CGame* g)
    {
        m_pParent = g;
    };

    CGame* m_pParent{ nullptr };                        //存放一个CGame类的指针在本中

    virtual void Draw(Graphics& gh) const;              //画自己

    RectF m_rect{ 0, 0, 800, 600 };                     //自己的范围

    void OnMouseMove(UINT nFlags, CPoint point);        //处理 鼠标移动事件

    void OnLButtonUp(UINT nFlags, CPoint point);        //处理 鼠标左键抬起事件

    Image* m_imgBackground;                             //背景图片指针

    struct {                                            //菜单项
        vector<tuple<Image*, RectF>> vImgInfoPtr;       //图片指针和范围
        int index;                                      //图片标号
    } m_menuItems[2];
};
