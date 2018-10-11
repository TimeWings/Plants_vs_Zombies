#pragma once
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;
class Bullet : public Entity
{
private:
	int _Damage;
	double _Speed;
	virtual void Hit_Animation() = 0;
	virtual void Self_Animation() = 0;
public:
	Bullet(Sprite* img, Point position, int damage, double speed);
	int getDamage();
	void setDamage(int damage);
	double getSpeed();
	void setSpeed(double speed);
	virtual void move() = 0;
};