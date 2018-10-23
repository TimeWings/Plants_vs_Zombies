#pragma once
#include "cocos2d.h"
USING_NS_CC;
class BulletLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	static BulletLayer* create();
	static BulletLayer* getInstance()
	{
		return pRet;
	}
	static BulletLayer *pRet;
private:
	void Check_Collision(float t);
	void Check_Death(float t);
};
