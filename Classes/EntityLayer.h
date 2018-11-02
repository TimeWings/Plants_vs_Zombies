#pragma once
#include "cocos2d.h"
USING_NS_CC;
class EntityLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	static EntityLayer* create();
	static EntityLayer* getInstance()
	{
		return pRet;
	}
	static EntityLayer *pRet;
private:
	void Check_Collision(float t);
	void Check_Death(float t);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchEened(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void Check_isAttack_Zombie(float t);
	void Check_Lost_head_Zombie(float t);
	void Check_isAttack_Plant(float t);
	void clearNode(Node * pSender);
};
