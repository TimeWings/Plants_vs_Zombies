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
	schedule(schedule_selector(BulletLayer::Check_Collision), 0.1);
	this->schedule(schedule_selector(BulletLayer::Check_Death), 0.1);
	return true;
}
void BulletLayer::Check_Collision(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < readyBullet.size(); i++) 
	{
		Bullet*bullet = readyBullet.at(i);
		Sprite*sp = bullet->getImg();
		std::vector<int>*range=bullet->getRange();
		for (int j = 0; j < readyZombies.size(); j++)
		{
			Zombie*zombie = readyZombies.at(j);
			int ZombieRow = zombie->getRow();
			bool flag = false;
			for (int k = 0; k < range->size(); k++)
			{
				
				if (range->at(k) == ZombieRow)
				{
					flag = true;
					break;
				}
			}
			if (!flag)continue;
			if (sp->boundingBox().intersectsRect(zombie->getImg()->getBoundingBox()))
			{
				std::cout << "子弹碰撞了" << std::endl;
				bullet->cal_damage(zombie);
				bullet->Hit_Animation(zombie);
				
			}
		}
	}
}

void BulletLayer::Check_Death(float t)
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
}


