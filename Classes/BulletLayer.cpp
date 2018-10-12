#include "BulletLayer.h"
#include "Global.h"
#include <iostream>
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
	this->schedule(schedule_selector(BulletLayer::test), 0.1);
	this->schedule(schedule_selector(BulletLayer::test1), 6);
	return true;
}

//子弹生成
void BulletLayer::Produce_Bullets(float t) {
	for (auto x : preBullet.keys()) {
		Sprite* sp = preBullet.at(x);
		this->addChild(sp);

		Sprite * hole = Sprite::create("circle.png");
		hole->setPosition(Vec2(sp->getPositionX()- sp->getContentSize().width*sp->getScale()/2,sp->getPositionY()));
		this->addChild(hole);
		ActionInterval * fadeout = FadeOut::create(0.3);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(BulletLayer::clear1, this));
		Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
		hole->runAction(sequence);

		readyBullet.insert(x,sp);
		x->move(sp);
		preBullet.erase(x);
	}
}

void BulletLayer::test(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto x : readyBullet.keys())
	{
		Sprite*sp = readyBullet.at(x);
		if (sp->getPositionX() > visibleSize.width - 200)
		{
			//std::cout << "闪闪击中僵尸" << std::endl;
			x->Hit_Animation(sp);
			
		}
	}
}
void BulletLayer::test1(float t) 
{
	for (auto x : readyPlants.keys())
	{
		Sprite *sp = readyPlants.at(x);
		x->Die(sp);
	}
}
void BulletLayer::clear1(Node *pSender)
{
	//std::cout << "闪闪的剑洞被清除了" << std::endl;
	pSender->removeFromParent();
}

