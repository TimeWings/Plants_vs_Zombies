#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include "Plants.h"
USING_NS_CC;
class iceCabbage : public Plants
{
private:
	Point position;
public:
	iceCabbage(Point position, int row);
	virtual bool isWorking();//是否能工作
	virtual void work();
	virtual void Die();
	void iceWorld(Node *pSender);
	void freezeZombie(Zombie * zombie);
	virtual void Attacked();
	//产生子弹
	virtual void CreateBullet();
	void clearIceSprite(Node * pSender, Sprite * iceSprite, Zombie* zombie);
	//清理精灵
	void clear(Node * pSender);
};