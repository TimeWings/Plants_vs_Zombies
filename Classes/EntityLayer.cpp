#include "EntityLayer.h"
#include "Global.h"
#include "Zombie.h"
#include "Bullet.h"
#include "PaulBullet.h"
#include <stdio.h>
#include <math.h>
#include <sys/timeb.h>
#include <time.h>
#include <iostream>
using namespace map;
EntityLayer* EntityLayer::pRet = NULL;
EntityLayer* EntityLayer::create()
{
	EntityLayer::pRet = new EntityLayer();
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
bool EntityLayer::init()
{
	this->PaulReady = false;
	schedule(schedule_selector(EntityLayer::Check_Collision), 0.1);
	this->schedule(schedule_selector(EntityLayer::Check_Death), 0.1);
	//这里写时间定时器
	this->setTouchEnabled(true);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(EntityLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(EntityLayer::onTouchEnded, this);
	listener->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->schedule(schedule_selector(EntityLayer::Check_isAttack_Zombie), 0.1);
	this->schedule(schedule_selector(EntityLayer::Check_Lost_head_Zombie), 0.1);
	this->schedule(schedule_selector(EntityLayer::Check_isAttack_Plant), 0.1);
	this->schedule(schedule_selector(EntityLayer::Check_Death), 0.1);
	return true;
}
void EntityLayer::Check_Collision(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		Bullet*bullet = readyBullet.at(i);
		Sprite*sp = bullet->getImg();
		std::vector<int>*range = bullet->getRange();
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
				bullet->Hit_Animation(zombie);
				if (sp->getTag() == Penetrable_tag)
				{
					zombie->DamageBoth(bullet->getDamage());
				}
				else if (sp->getTag()== Pitcher_tag)
				{
					zombie->DamageZombie(bullet->getDamage());
				}
				else
				{
					zombie->DamageEquip(bullet->getDamage());
				}

			}
		}
	}
}

bool EntityLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Point touchPos = touch->getLocation();
	for (auto x : readySun.keys())
	{
		Sprite *sun = readySun.at(x);
		if (touchPos.x > sun->getPositionX() - sun->getContentSize().width / 2 * sun->getScaleX() && touchPos.x < sun->getPositionX() + sun->getContentSize().width / 2 * sun->getScaleX()
			&& touchPos.y< sun->getPositionY() + sun->getContentSize().height / 2 * sun->getScaleY() && touchPos.y>sun->getPositionY() - sun->getContentSize().height / 2 * sun->getScaleY())
		{
			sunCnt.first++;
			Plants *plant;
			for (int i = 0; i < readyPlants.size(); i++)
			{
				if (readyPlants.at(i)->getImg() == x)
				{
					plant = readyPlants.at(i);
				}
			}
			struct timeb t1;
			ftime(&t1);
			long long seconds = t1.time * 1000 + t1.millitm;
			plant->setBirthTime(seconds);
			//std::cout << "获得太阳，当前太阳数：" << sunCnt.first << std::endl;
			Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sun);
			MoveTo *moveTo = MoveTo::create(2, ccp(sunCnt.second.first, sunCnt.second.second));
			CCActionInterval * rotate = CCRotateTo::create(2, 180);
			CCFiniteTimeAction * spawn = CCSpawn::create(moveTo, rotate, NULL);
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(EntityLayer::clearNode, this));
			CCFiniteTimeAction * reveseseq = CCSequence::create(spawn, actionDone, NULL);
			sun->runAction(reveseseq);
			readySun.erase(x);
		}
	}
	return false;
}
void EntityLayer::onTouchEened(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
}

//检测植物是否工作
void EntityLayer::Check_isAttack_Plant(float t)
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		Plants* x = readyPlants.at(i);
		struct timeb t1;
		ftime(&t1);
		long long seconds = t1.time * 1000 + t1.millitm;
		long long interval = seconds - x->getBirthTime();
		//std::cout << interval<<"   "<< x->getInterval() << std::endl;
		//long long a = (interval / 100L) * 100;
		if (interval > x->getInterval()) {
			//调用工作函数
			x->work();
		}
	}
}

void EntityLayer::Check_isAttack_Zombie(float t)
{
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie *zombie = readyZombies.at(i);
		if (!zombie->hasHead()) continue;
		Sprite *sp = zombie->getImg();
		Plants *p;
		bool flag = false;
		double zombiex = sp->getPositionX();
		for (int j = 0; j < readyPlants.size(); j++)
		{
			Plants *plant = readyPlants.at(j);
			Sprite *sp_plant = plant->getImg();
			int row = plant->getRow();
			int zombieRow = zombie->getRow();
			double plantx = Rank2Point(plant->getRow(), plant->getCol()).x;

			if (row!= zombieRow)
			{
				continue;
			}
			//std::cout << sp->getPositionY() << " " << Rank2Point(plant->getRow(), plant->getCol()).y << std::endl;
			if (sp->getPositionY() == Rank2Point(plant->getRow(), plant->getCol()).y && zombiex >= plantx && zombiex - plantx <= (sp->getContentSize().width)*(sp->getScaleX()) * 0.35 + (sp_plant->getContentSize().width)*(sp_plant->getScaleX()) * 0.35)
			{
				flag = true;
				p = plant;
			}
		}
		if (zombie->isMeeting() && !flag) {
			std::cout << "移动" << std::endl;
			zombie->Move();
			zombie->setMeeting(false);
		}
		else if (!zombie->isMeeting() && flag) {
			zombie->Attack(p);
			zombie->setMeeting(true);
		}
	}
}

void EntityLayer::Check_Lost_head_Zombie(float t) {
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie *zombie = readyZombies.at(i);
		if (zombie->getHp() <= 2 && zombie->hasHead()) {
			zombie->LostHead();
		}
	}
}

void EntityLayer::Check_Death(float t)
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
	/*for (int j = 0; j < readyZombies.size(); j++)
	{
		Zombie* zombie = readyZombies.at(j);
		Sprite* sp = zombie->getImg();
		if (zombie->getHp() <= 0)
		{
			zombie->Die();
			j--;
		}
	}*/
}

void EntityLayer::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}

