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
	Bullet();
	Bullet(Point position, int damage, double speed);
	int getDamage();
	void setDamage(int damage);
	double getSpeed();
	void setSpeed(double speed);
	virtual void work(Sprite* sp) = 0;
	virtual void move(Sprite* sp) = 0;
	virtual void Hit_Animation(Sprite * sp, std::vector<int>debuff,int tag) = 0;
	virtual Sprite * attack_Animation(Sprite * sp)=0;
};