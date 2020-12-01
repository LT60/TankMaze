#pragma once
//CGame类代表“整个游戏”对象
class CGame
{

public:
	//添加鼠标响应功能：
	void SetHandle(HWND hWnd);					//设置输出窗口的句柄
	bool EnterFrame(DWORD dwTime);				//进入游戏帧
	void OnMouseMove(UINT nFlags, CPoint point);//处理鼠标移动事件
	void OnLButtonUp(UINT nFlags, CPoint point);//处理左键抬起事件
private:
	HWND m_hWnd;								//窗口

	//1.5.3游戏绘图处理
	//负责绘画游戏中的对象（游戏所有的绘图操作都会经过这里分发）
	void GameRunDraw();
	//输出fps
	void Drawfps(Graphics& gh);
	//记录帧率
	int m_fps{ 0 };
};
