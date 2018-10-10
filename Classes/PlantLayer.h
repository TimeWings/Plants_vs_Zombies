#pragma once
#include "cocos2d.h"
USING_NS_CC;
class PlantLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	static PlantLayer* create();
private:
	void Produce_Plants(float t);
};