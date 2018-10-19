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
	void test(float t);
	void test2(float t);
	void test3(float t);
};
