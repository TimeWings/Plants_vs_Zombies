#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"
USING_NS_CC;
class Plants:public Entity
{
private:
	int _Hp; //血量
	long long BirthTime; //诞生时间
	long long _BulletInterval; //攻击间隔
public:
	Plants(); //构造函数
	int getHp(); 
	void setHp(int hp);
	long long getInterval(); 
	void setInterval(long long BulletInterval);
	long long getBirthTime();
	void setBirthTime(long long seconds);
	virtual void init() = 0; //初始化
	virtual void work() = 0; //工作
	virtual void Die() = 0; //
	virtual void Attacked() = 0;
	virtual bool isAttacking() = 0;
};