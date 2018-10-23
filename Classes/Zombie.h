#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "ZombieLayer.h"
#include "Plants.h"
USING_NS_CC;

class Zombie : public Entity 
{
private:
	int _Hp; //血量
	//long long BirthTime; //诞生时间
	double _BiteInterval; //攻击间隔
	int _WalkSpeed; //移动速度
	bool _Head;
	bool _meeting;
	std::vector<int> debuff;
	CCScheduler *sched;

public:
	Zombie(); //构造函数
	int getHp();
	void setHp(int hp);
	double getInterval();
	void setInterval(double BiteInterval);
	int getWalkSpeed();
	void setWalkSpeed(int WalkSpeed);
	bool hasHead();
	void setHead(bool Head);
	bool isMeeting();
	void setMeeting(bool meeting);
	std::vector<int> getDebuff();
	void addLayer(Node* entity);
	void setActionManger(Node * sprite);
	virtual void attack(Plants *plant) = 0; //工作
	virtual bool isAttacking() = 0;
	virtual void Die() = 0;
	virtual void Attacked() = 0;
	virtual void LostHead() = 0;
	virtual void Move() = 0;
};