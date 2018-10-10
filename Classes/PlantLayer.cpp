#include "PlantLayer.h"
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
	return true;
}

//植物生成
void PlantLayer::Produce_Plants(float t) {

}