#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class GraveBuster :public Plants
{
private:
	bool isEating=false;
	Plants* plant=NULL;
public:
	GraveBuster(Point position, int row, int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	void readyDie(Node * pSender);
	virtual void Die();
	//被打之后的事件
	virtual void Attacked();
	//清理精灵
	void clear(Node * pSender);
};
