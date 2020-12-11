#pragma once
#include <gdiplus.h>
#include <math.h>
#include <cmath>

class CGameEntry
{
public:
    CGameEntry()              // 构造函数：产生新对象时调用
    {
    }

    virtual ~CGameEntry()    // 构造函数：销毁对象时调用
    {
    }
public:
    virtual void Draw(Gdiplus::Graphics& gh) const = 0; // 用于绘制自己的纯虚函数
};

// 可移动的物体
class CGameEntryMoveable : public CGameEntry
{
public:
    CGameEntryMoveable()                                    // 构造函数：产生新对象时调用
    {
    }

    virtual ~CGameEntryMoveable()                          // 构造函数：销毁对象时调用
    {
    }

    // 拷贝构造方法
    CGameEntryMoveable(const CGameEntryMoveable& rhs)
    {
        if (this != &rhs) {
            this->m_bActive = rhs.m_bActive;				// 是否有效
            this->m_rect = rhs.m_rect;						// 占用的区域
            this->m_fSpeed = rhs.m_fSpeed;					// 移动速度
            this->m_direction = rhs.m_direction;			// 当前的角度
            this->m_directionTurn = rhs.m_directionTurn; 	// 每次旋转的角度
        }
    }

    // 重载赋值运算
    CGameEntryMoveable& operator=(const CGameEntryMoveable& rhs)
    {
        if (this != &rhs) {
            this->m_bActive = rhs.m_bActive;				// 是否有效
            this->m_rect = rhs.m_rect;						// 占用的区域
            this->m_fSpeed = rhs.m_fSpeed;					// 移动速度
            this->m_direction = rhs.m_direction; 			// 当前的角度
            this->m_directionTurn = rhs.m_directionTurn; 	// 每次旋转的角度
        }
        return *this;
    }
public:
    virtual void Draw(Gdiplus::Graphics& gh) const = 0;

    /********************可移动物体的 共同属性********************/
    // 右转
    virtual void RotateRight()
    {

        m_direction += m_directionTurn; // 当前角度增加
        if (m_direction >= 360) {         // 增加满一周之后，减去360度，使其始终保持在小角度
            m_direction -= 360;
        }
    }

    // 左转
    virtual void RotateLeft()
    {
        m_direction -= m_directionTurn; // 当前角度减少
        if (m_direction < 0) {            // 使其始终保持在大于0的角度
            m_direction = static_cast<float>(360 - m_directionTurn);
        }
    }

    // 前移动
    virtual void Forward()
    {
        // 根据当前角度，在x,y方向上分别进行增减
        m_rect.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
        m_rect.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
    }

    // 后移动
    virtual void Backward()
    {
        // 根据当前角度，在x,y方向上分别进行增减
        m_rect.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
        m_rect.Y += static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
    }

    // 获得平方向的速度分量
    virtual float GetXSpeed() const
    {
        return static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
    }

    // 获得坚直方向的速度分量
    virtual float GetYSpeed() const
    {
        return -static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
    }

    // 下一步(前进的)位置
    virtual RectF ForwardNextRect() const
    {
        RectF rc = m_rect;
        rc.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
        rc.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
        return rc;
    }

    // 下一步(后退的)位置
    virtual RectF BackwardNextRect() const
    {
        RectF rc = m_rect;
        rc.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
        rc.Y += static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
        return rc;
    }

    // 获取头部位置 : 图片为矩型：头部位置 就是角度为0时，
    // 距离中心点为半径（对角线/2)长度，重值于自己的 X轴的位置
    virtual PointF GetHeadPos() const
    {
        PointF ptCenter = GetCenterPoint();
        PointF ptHead = ptCenter;
        float fRadius = std::sqrt(std::pow(m_rect.Width / 2, 2) +   // 计算半径
            std::pow(m_rect.Height / 2, 2));

        ptHead.X += fRadius * sin(GetDirectionArc());                // 计算头部坐标x
        ptHead.Y -= fRadius * cos(GetDirectionArc());                // 计算头部坐标y
        return ptHead;                                                  // 返回头部坐标
    }

    // 获取中心点
    virtual PointF GetCenterPoint()const
    {
        PointF center = PointF(m_rect.X + m_rect.Width / 2,
            m_rect.Y + m_rect.Height / 2);
        return center;
    }

    // 设置中心点
    virtual void SetCenterPoint(const PointF& ptCenter)
    {
        PointF cen = GetCenterPoint();
        cen.X = ptCenter.X - cen.X;
        cen.Y = ptCenter.Y - cen.Y;
        m_rect.Offset(cen);
    }

    // 属性存取器
#ifndef PI
#define PI (3.1415926f)
#endif
    // 设置角度 : 单位为 a*PI
    virtual void SetDirectionArc(float dir)
    {
        m_direction = dir * 180.0f / PI;
    };

    // 设置角度(单位是 度)
    virtual void SetDirection(float dir)
    {
        m_direction = dir;
    }

    // 获得当前的角度(单位是 a*PI)
    virtual float GetDirectionArc() const
    {
        return PI * m_direction / 180.0f;
    }

    // 获得当前的角度(单位是 度)
    virtual float GetDirection() const
    {
        return m_direction;
    }

    // 设置每次旋转的角度
    virtual void SetDirectionTurnArc(float dir)
    {
        m_directionTurn = PI * dir / 180.0f;
    };

    // 设置每次旋转的角度
    virtual void SetDirectionTurn(float dir)
    {
        m_directionTurn = dir;
    }

    // 获得当前的角度(单位是 PI)
    virtual float GetDirectionTurnArc() const
    {
        return PI * m_directionTurn / 180.0f;
    }

    // 获得当前的弧度(单位是度)
    virtual float GetDirectionTurn() const
    {
        return m_direction;
    }

    // 是否是有效的
    virtual  bool IsActive() const
    {
        return m_bActive;
    };

    // 是否是有效的
    virtual void SetActive(bool bActive)
    {
        m_bActive = bActive;
    }

    // 占用范围
    virtual void SetRect(const RectF rect)
    {
        m_rect = rect;
    }

    // 占用范围
    virtual RectF GetRect() const
    {
        return m_rect;
    }

    // 移动速度
    virtual void SetSpeed(float speed)
    {
        m_fSpeed = speed;
    }

    // 移动速度
    virtual float GetSpeed() const
    {
        return m_fSpeed;
    }

private:
    bool m_bActive{ false };  		// 是否有效
    RectF m_rect{ 0, 0, 100, 100 }; // 占用的区域
    float m_fSpeed{ 10 }; 			// 移动速度
    float m_direction{ 0 }; 		// 当前的角度
    float m_directionTurn{ 5 }; 	// 每次旋转的角度
};
