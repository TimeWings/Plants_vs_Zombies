#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Zombie.h"
USING_NS_CC;

class ZombieEquipment : public Entity
{
private:
	int _Hp;
	bool _Metal;
public:
	int getHp();
	void setHp(int Hp);
	bool isMetal();
	void setMetal(bool Metal);
	void addLayer(Node* entity, Zombie* zombie);
	virtual void Die() = 0;
};