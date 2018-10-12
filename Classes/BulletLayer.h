#pragma once
#include "cocos2d.h"
USING_NS_CC;
class BulletLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	static BulletLayer* create();
private:
	void Produce_Bullets(float t);
	void test(float t);
	void test1(float t);
	void clear1(Node * pSender);
};
