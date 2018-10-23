#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include "Entity.h"
#include "test.h"
USING_NS_CC;
class Bullet : public Entity
{
private:
	int _Damage;
	double _Speed;
	std::vector<int>range;
public:
	Bullet();
	Bullet(Point position, int damage, double speed);
	int getDamage();
	void setDamage(int damage);
	double getSpeed();
	void setSpeed(double speed);
	std::vector<int> *getRange();
	//计算伤害（扣僵尸的血量）
	void cal_damage(Zombie * zombie);
	//直接添加到子弹层
	void addLayer(Node* entity);
	//子弹路径移动
	virtual void move() = 0;
	//僵尸被该子弹攻击之后的效果（减速，debuff）
	virtual void Hit_Animation(Zombie * zombie) = 0;
};