#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
USING_NS_CC;

class IceBullet :public PeaBullet
{
public:
	IceBullet(Point position);
	virtual void work();
	virtual void Hit_Animation(Sprite * sp, std::vector<int>debuff, Vector<Action*>action);
	virtual Sprite * attack_Animation();
	void Self_Animation();
	void resume(Node * pSender, Action * action, std::vector<int>debuff);
};