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
	void Check_isAttack(float t);
	void Produce_Plants(float t);
};