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
	static PlantLayer* getInstance()
	{
		return pRet;
	}
	static PlantLayer *pRet;
private:
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchEened(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void Check_isAttack(float t);
	void clearNode(Node * pSender);
};