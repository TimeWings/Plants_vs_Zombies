#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include <vector>
USING_NS_CC;
class PlantLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	static PlantLayer* create();
private:
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchEened(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void Check_isAttack(float t);
	void Produce_Plants(float t);
	void Produce_Sun(float t);
	void clear(Node * pSender);
	void clear1(Node * pSender, Sprite *sunFlower);
};