#include "PlantLayer.h"
#include "Global.h"
#include "PeaShooter.h"
#include <iostream>
#include "Plants.h"
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
	//Produce_Plants(0.5);
	this->scheduleOnce(schedule_selector(PlantLayer::Produce_Plants), 1);
	//this->schedule(schedule_selector(PlantLayer::prepareBullet), 1);
	return true;
}

//植物生成
void PlantLayer::Produce_Plants(float t) {
	if (prePlants.size() > 0) {
		Plants *plant = prePlants.at(0);
		std::cout << plant << std::endl;
		this->addChild(plant->getImg());
		prePlants.erase(prePlants.begin());
		
	}
	
	//Plants *plant = new PeaShooter(Point(130, 180));
	//std::cout << plant << std::endl;
	//prePlants.push_back(plant);
	/*Plants* p = prePlants.front();
	std::cout << p << std::endl;
	this->addChild(p->getImg());
	prePlants.erase(prePlants.begin());*/
}

//void PlantLayer::prepareBullet(float t) {
//	/*for (int i = 0; i < readyPlants.size(); i++) {
//		Plants *plant = prePlants.at(i);
//		plant->CreateBullet();
//	}*/
//	
//}