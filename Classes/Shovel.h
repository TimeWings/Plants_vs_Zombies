#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class Shovel :public Plants
{
public:
	Shovel(Point position, int row, int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	//特有的自身动画
	void Self_Animation();
	//被打之后的事件
	virtual void Attacked();
	//清理精灵
	void clear(Node * pSender);


};
