#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "ZombieLayer.h"
USING_NS_CC;

class Zombie : public Entity 
{
private:
	int _Hp; //血量
	long long BirthTime; //诞生时间
	long long _BiteInterval; //攻击间隔
	int _WalkSpeed; //移动速度
	bool _Head;
	bool _Hand;
	std::vector<int> debuff;
	CCScheduler *sched;

public:
	Zombie(); //构造函数
	int getHp();
	void setHp(int hp);
	long long getInterval();
	void setInterval(long long BiteInterval);
	long long getBirthTime();
	void setBirthTime(long long seconds);
	int getWalkSpeed();
	void setWalkSpeed(int WalkSpeed);
	bool hasHead();
	void setHead(bool Head);
	bool hasHand();
	void setHand(bool Hand);
	std::vector<int> getDebuff();
	void addLayer(Node* entity);
	void setActionManger(Node * sprite);
	virtual void attack() = 0; //工作
	virtual bool isAttacking() = 0;
	virtual void Die() = 0;
	virtual void Attacked() = 0;
	virtual void LostHand() = 0;
	virtual void LostHead() = 0;
};