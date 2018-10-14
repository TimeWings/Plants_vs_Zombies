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
	this->schedule(schedule_selector(BulletLayer::Produce_Bullets), 0.01);
	//this->schedule(schedule_selector(BulletLayer::test), 0.1);
	return true;
}


//子弹生成
void BulletLayer::Produce_Bullets(float t) {
	if (preBullet.size() != 0) 
	{
		Bullet* bullet = preBullet.front();
		Sprite *sp = bullet->getImg();
		this->addChild(sp);
		Sprite *hole = bullet->attack_Animation();
		if (hole != NULL)
		{
			this->addChild(hole);
		}
		readyBullet.push_back(bullet);
		bullet->work();
		bullet->move();
		preBullet.erase(preBullet.begin());
	}
}

//void BulletLayer::test(float t)
//{
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	for (int i = 0; i < readyBullet.size(); i++) 
//	{
//		Bullet*bullet = readyBullet.at(i);
//		Sprite*sp = bullet->getImg();
//		for (int j = 0; j < testMap.size(); j++)
//		{
//			if (sp->boundingBox().intersectsRect(testMap.at(j)->getBoundingBox()))
//			{
//				std::cout << "碰撞了" << std::endl;
//				bullet->Hit_Animation(y, debuff, );
//			}
//		}
//	}
//	for (auto x : readyBullet.keys())
//	{
//		Sprite* bullet = readyBullet.at(x);
//		for (auto y : testMap)
//		{
//			if (bullet->boundingBox().intersectsRect(y->getBoundingBox()))
//			{
//				std::cout << "碰撞了" << std::endl;
//				x->Hit_Animation(y, debuff,100);
//			}
//		}
//	}
//}
void BulletLayer::clear1(Node *pSender)
{
	//std::cout << "闪闪的剑洞被清除了" << std::endl;
	pSender->removeFromParent();
}

