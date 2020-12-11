#pragma once

#include <tuple>
#include <vector>           //C++��׼���еĶ�̬����
#include "GameEntry.h"

using namespace std;

class CGame;                //ǰ������CGame��

class CGameMenuPanel : public CGameEntryMoveable    //�̳��Կ��ƶ�����
{
public:
    CGameMenuPanel();
    ~CGameMenuPanel();

    // ���һ��CGame���ָ���ڱ���
    void SetParent(CGame* g)//������Ϸ���Ŀ�ܵ�ָ��
    {
        m_pParent = g;
    };
    CGame* m_pParent{ nullptr };                        //��ţ�һ��CGame���ָ���ڱ��У�

    virtual void Draw(Graphics& gh) const;              //���Լ����̳��Ը���

    RectF m_rect{ 0, 0, 800, 600 };                     //�Լ��ķ�Χ

    void OnMouseMove(UINT nFlags, CPoint point);        //��������ƶ��¼���
        void OnLButtonUp(UINT nFlags, CPoint point);    //����������̧���¼���

    Image* m_imgBackground;                             //����ͼƬָ��

    struct {                                            //�˵���
        vector<tuple<Image*, RectF>> vImgInfoPtr;       //ͼƬָ��ͷ�Χ
        int index;                                      //ͼƬ���
    } m_menuItems[2];
};
