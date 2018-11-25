#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "Zombie.h"
#define self_tag 99999
USING_NS_CC;
class Chomper:public Plants
{
private:
	bool isEating = false;
public:
	Chomper(Point position, int row, int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	void Eat(Zombie * zombie);
	void resume(Node * pSender);
	//特有的自身动画
	void Self_Animation();
	//被打之后的事件
	virtual void Attacked();
	//清理精灵
	void clear(Node * pSender);
	void clear1(Node * pSender, Sprite * sp);
};
