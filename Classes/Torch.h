#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "Bullet.h"
USING_NS_CC;
class Torch :public Plants
{
public:
	Torch(Point position, int row, int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	virtual void Die();
	//特有的自身动画
	void Self_Animation();
	//被打之后的事件
	virtual void Attacked();
	//产生子弹
	virtual void CreateBullet(Bullet*bullet);
	//清理精灵
	void clear(Node * pSender);
};
