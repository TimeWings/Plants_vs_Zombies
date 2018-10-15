#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"
USING_NS_CC;
class TestZombie : public Entity
{
public:
	int _hp;
	double _Speed;
    CCScheduler *sched1;
    std::vector<int> debuff;
	TestZombie(Point position);
	Sprite * init();
	
};
