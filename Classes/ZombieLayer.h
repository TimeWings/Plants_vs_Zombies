#pragma once
#include "Zombie.h"
#include <sys/timeb.h>
#include <ctime>

class ZombieLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	static ZombieLayer* create();
	static ZombieLayer* getInstance()
	{
		return pRet;
	}
	static ZombieLayer *pRet;
private:
	void Check_isAttack(float t);
	void Check_Death(float t);
	void clearNode(Node * pSender);
};