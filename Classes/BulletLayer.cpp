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
	for (int i = 0;i<preBullet.size();i++) {
		Bullet *bullet = preBullet.at(i);
		this->addChild(bullet->getImg(),1);
		readyBullet.push_back(preBullet.at(i));
		bullet->move();
		preBullet.erase(preBullet.begin() + i);
		i--;
	}
}

