#pragma once
#include "Entity.h"
#include "cocos2d.h"
USING_NS_CC;

class Zombie : public Entity {
private:
	int _Hp; //血量
	long long BirthTime; //诞生时间
	long long _BiteInterval; //攻击间隔
	int _WalkSpeed; //移动速度
	int _WalkDirection; //移动方向
	bool _Head;
	bool _Hand;

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
	int getWalkDirection();
	void setWalkDirection(int WalkDirection);
	bool hasHead();
	void setHead(bool Head);
	bool hasHand();
	void setHand(bool Hand);
	virtual void init() = 0; //初始化
	virtual void work() = 0; //工作
	virtual void Die() = 0; //
	void Self_Animation();
};