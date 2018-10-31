#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class Doom_shroom :public Plants
{
private:
	Point position;
public:
	Doom_shroom(Point position, int row, int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	virtual void Die();
	void Boom(Node * pSender);
	void clearSprite(Node * pSender, Sprite * sp);
	void zombiesDie(Node * pSender);
	//特有的自身动画
	void Self_Animation();
	//被打之后的事件
	virtual void Attacked();
	//产生子弹
	virtual void CreateBullet();
	//清理精灵
	void clear(Node * pSender);
};