#include "BulletLayer.h"
#include "Global.h"
#include <iostream>
BulletLayer* BulletLayer::pRet=NULL;
BulletLayer* BulletLayer::create()
{
	BulletLayer::pRet = new BulletLayer();
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
	schedule(schedule_selector(BulletLayer::test), 0.1);

	this->schedule(schedule_selector(BulletLayer::test2), 0.1);
	this->schedule(schedule_selector(BulletLayer::test3), 0.1);
	return true;
}
void BulletLayer::test(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < readyBullet.size(); i++) 
	{
		Bullet*bullet = readyBullet.at(i);
		Sprite*sp = bullet->getImg();
		for (int j = 0; j < testMap.size(); j++)
		{
			if (sp->boundingBox().intersectsRect(testMap.at(j)->getImg()->getBoundingBox()))
			{
				std::cout << "子弹碰撞了" << std::endl;
				bullet->cal_damage(testMap.at(j));
				bullet->Hit_Animation(testMap.at(j));
				
			}
		}
	}
}

void BulletLayer::test2(float t)
{
	for (int j = 0; j < readyPlants.size(); j++)
	{
		Plants* plant = readyPlants.at(j);
		Sprite* sp = plant->getImg();
		if (plant->getHp() <= 0)
		{
			plant->Die();
			j--;
		}
	}
	for (int j = 0; j < testMap.size(); j++)
	{
		TestZombie* zb = testMap.at(j);
		Sprite* sp = zb->getImg();
		if (zb->_hp <= 0)
		{
			std::cout << "这个僵尸死了" << std::endl;
			testMap.erase(testMap.begin()+j);
			j--;
			sp->removeFromParent();
		}

	}
}
void BulletLayer::test3(float t)
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		Plants*plant = readyPlants.at(i);
		Sprite*sp = plant->getImg();
		for (int j = 0; j < testMap.size(); j++)
		{
			if (sp->boundingBox().intersectsRect(testMap.at(j)->getImg()->getBoundingBox()))
			{
				std::cout << "碰撞了" << std::endl;
				plant->getHurt(1);
				plant->Attacked();

			}
		}
	}
}


