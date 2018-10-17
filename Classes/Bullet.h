#pragma once
#include "cocos2d.h"
#include "TestZombie.h"
#include "Entity.h"
#include "test.h"
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
	void cal_damage(TestZombie* zombie);
	void addLayer(Node* entity);
	virtual void move() = 0;
	virtual void Hit_Animation(TestZombie* zombie) = 0;
};