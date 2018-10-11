#include "PlantLayer.h"
#include "Global.h"
#include "PeaShooter.h"
#include <iostream>
#include "Plants.h"
#include <stdio.h>
#include <math.h>
PlantLayer* PlantLayer::create()
{
	PlantLayer *pRet = new PlantLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}
bool PlantLayer::init() {
	//这里写时间定时器
	this->schedule(schedule_selector(PlantLayer::Produce_Plants), 1);
	this->schedule(schedule_selector(PlantLayer::Check_isAttack), 1);
	return true;
}

void PlantLayer::Check_isAttack(float t)
{
	for (auto x : readyPlants.keys()) {
		int seconds = time((time_t*)NULL);
		int interval = seconds - x->getBirthTime();
		if (fmod(interval, x->getInterval()) == 0) {
			x->CreateBullet(readyPlants.at(x));
		}
	}
}

//植物生成
void PlantLayer::Produce_Plants(float t) {
	for (auto x : prePlants.keys()) {
		Sprite*sp = prePlants.at(x);
		this->addChild(sp);
		int seconds = time((time_t*)NULL);
		x->setBirthTime(seconds);
		readyPlants.insert(x, sp);
		prePlants.erase(x);
	}
	
}
