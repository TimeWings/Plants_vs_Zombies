#pragma once
//#include "Entity.h"
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;

#define Animation_Tag 1

class Zombie : public Entity 
{
private:
	int _Hp; //血量
	//long long BirthTime; //诞生时间
	double _BiteInterval; //攻击间隔
	int _WalkSpeed; //移动速度
	bool _Head;
	bool _meeting;
	int _row;
	std::vector<int>range;
	std::vector<int> debuff;
	CCScheduler *sched;

public:
	Zombie(); //构造函数
	int getHp();
	void setHp(int hp);
	int getRow();
	void setRow(int row);
	double getInterval();
	void setInterval(double BiteInterval);
	int getWalkSpeed();
	void setWalkSpeed(int WalkSpeed);
	bool hasHead();
	void setHead(bool Head);
	bool isMeeting();
	void setMeeting(bool meeting);
	std::vector<int>*getRange();
	std::vector<int>*getDebuff();
	void addLayer(Node* entity);
	void setSche(Node * sprite);
	CCScheduler* getScheduler();
	virtual void attack(Plants *plant) = 0; //工作
	virtual bool isAttacking() = 0;
	virtual void Die() = 0;
	virtual void Attacked() = 0;
	virtual void LostHead() = 0;
	virtual void Move() = 0;
};