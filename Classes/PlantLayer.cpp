#include "PlantLayer.h"
#include "Global.h"
#include "PeaShooter.h"
#include <iostream>
#include "Plants.h"
#include <stdio.h>
#include <math.h>
#include <sys/timeb.h>
#include <time.h>
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
	this->schedule(schedule_selector(PlantLayer::Check_isAttack), 0.1);
	return true;
}

void PlantLayer::Check_isAttack(float t)
{
	for (auto x : readyPlants.keys()) {
		//std::cout << readyPlants.at(x)->getPositionX()<<"  "<< readyPlants.at(x)->getPositionY() << std::endl;
		struct timeb t1;
		ftime(&t1);
		long long seconds = t1.time * 1000 + t1.millitm;
		long long interval = seconds - x->getBirthTime();
		//std::cout << (interval / 100L) * 100 << std::endl;
		long long a = (interval / 100L) * 100;
		if (a!=0&&(a% x->getInterval() == 0)) {
			x->work(readyPlants.at(x));
		}
	}
}

//植物生成
void PlantLayer::Produce_Plants(float t) {
	for (auto x : prePlants.keys()) 
	{
		Sprite*sp = prePlants.at(x);
		this->addChild(sp);
		
		struct timeb t1;
		ftime(&t1);
		long long seconds = t1.time * 1000+t1.millitm;
		//std::cout << seconds <<std:: endl;
		x->setBirthTime(seconds);
		readyPlants.insert(x, sp);
		x->init(sp);
		prePlants.erase(x);
	}
	
}
