#pragma once
//#include "Entity.h"
#include "cocos2d.h"
#include "Plants.h"
#include "ZombieEquipment.h"
#include "PlantStatus.h"
USING_NS_CC;

#define Animation_Tag 156347

class Zombie : public Entity 
{
private:
	int _Hp; //血量
	double _BiteInterval; //攻击间隔
	double  _WalkSpeed; //移动速度
	bool _Head;
	bool _meeting;
	int _row;
	int _col;
	std::vector<int> debuff;
	CCScheduler *sched;
	ZombieEquipment *equip;
protected:
	void setWalkSpeed(double WalkSpeed);
public:
	Zombie(); //构造函数
	int getHp();
	void setHp(int hp);
	int getRow();
	void setRow(int row);
	int getCol();
	void setCol(int col);
	double getInterval();
	void setInterval(double BiteInterval);
	double getWalkSpeed();//得到当前速度
	double getPreWalkSpeed();//得到原来的速度
	bool hasHead();
	void setHead(bool Head);
	bool isMeeting();
	void setMeeting(bool meeting);
	std::vector<int>*getDebuff();
	void addLayer(Node* entity);
	void setSche(Node * sprite);
	void setEquip(ZombieEquipment *equip);
	ZombieEquipment *getEquip();
	bool hasEquip();
	CCScheduler* getScheduler();
	virtual void Attack(PlantStatus *plantstatus) = 0;
	virtual void Die(Node * pSender) = 0;
	virtual void Attacked() = 0;
	virtual void LostHead() = 0;
	virtual void Move() = 0;
	virtual void DamageZombie(int damage) = 0;
	virtual void DamageEquip(int damage) = 0;
	virtual void DamageBoth(int damage) = 0;
	void DamagePlant(Node * pSender, PlantStatus *plantstatus);
};