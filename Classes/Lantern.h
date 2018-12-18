#pragma once
#include "Plants.h"
USING_NS_CC;
class Lantern :public Plants
{
private:
	Sprite* maskImg=NULL;
	bool isLightUp = false;
public:
	Lantern(Point position, int row, int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	//特有的自身动画
	void Self_Animation();
	//被打之后的事件
	virtual void Attacked();
	//清理精灵
	void clear(Node * pSender);
	virtual void Die();
};
