#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"
USING_NS_CC;
class Bullet : public Entity
{
private:
	int _Damage;
	double _Speed;
public:
	Bullet(Point position, int damage, double speed);
	int getDamage();
	void setDamage(int damage);
	double getSpeed();
	void setSpeed(double speed);
	virtual void move(Sprite* sp,Bullet* bullet) = 0;
	virtual void Hit_Animation(Sprite*sp) = 0;
	virtual void Self_Animation(Sprite*sp) = 0;
};