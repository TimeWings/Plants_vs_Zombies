#pragma once
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;
class Plants:public Entity
{
private:
	int _Hp;
	double _BulletInterval;
	virtual void Attack()=0;
	virtual void Die() = 0;
	virtual void Self_Animation() = 0;
	virtual void Attack_Animation() = 0;
	virtual void Attacked() = 0;
	bool isAttacking();
public:
	Plants(Sprite* img, Point position, int hp,double BulletInterval);
	int getHp();
	void setHp(int hp);
	double getInterval();
	void setInterval(double BulletInterval);
};