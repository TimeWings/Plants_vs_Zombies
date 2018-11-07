#pragma once
#include "Plants.h"
USING_NS_CC;
class Lotus :public Plants
{
public:
	Lotus(Point position, int row, int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	virtual void Die();
	//特有的自身动画
	void Self_Animation();
	//被打之后的事件
	virtual void Attacked();
	//清理精灵
	void clear(Node * pSender);

};
