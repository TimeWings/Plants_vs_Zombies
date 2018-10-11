#include "BulletLayer.h"
#include "Global.h"
BulletLayer* BulletLayer::create()
{
	BulletLayer *pRet = new BulletLayer();
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
bool BulletLayer::init() {
	//这里写时间定时器
	this->schedule(schedule_selector(BulletLayer::Produce_Bullets), 0.1);
	return true;
}

//子弹生成
void BulletLayer::Produce_Bullets(float t) {
	for (auto x : preBullet.keys()) {
		Sprite* sp = preBullet.at(x);
		this->addChild(sp);
		readyBullet.insert(x,sp);
		x->move(sp);
		preBullet.erase(x);
	}
}

