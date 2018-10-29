#include "EntityLayer.h"
#include "Global.h"
#include "Zombie.h"
#include "Bullet.h"
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
				bullet->cal_damage(zombie);
				bullet->Hit_Animation(zombie);
				zombie->Attacked();

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
		if (touchPos.x > sun->getPositionX() - sun->getContentSize().width / 2 * sun->getScale() && touchPos.x < sun->getPositionX() + sun->getContentSize().width / 2 * sun->getScale()
			&& touchPos.y< sun->getPositionY() + sun->getContentSize().height / 2 * sun->getScale() && touchPos.y>sun->getPositionY() - sun->getContentSize().height / 2 * sun->getScale())
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

//有BUG，当两个植物重叠放的时候，僵尸会播放攻击动画，但是没有对植物造成伤害
//有BUG，僵尸会攻击其自身后面的植物（不能用fbs判断）
//有BUG，不要设置太多标记（被大蒜赶跑后就不会攻击）
void EntityLayer::Check_isAttack_Zombie(float t)
{
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie *zombie = readyZombies.at(i);
		Sprite *sp = zombie->getImg();
		Plants *p;
		bool flagin = false, flagout = true;
		for (int j = 0; j < readyPlants.size(); j++)
		{
			Plants *plant = readyPlants.at(j);
			Sprite *sp_plant = plant->getImg();
			int row = plant->getRow();
			int zombieRow = zombie->getRow();

			if (row!= zombieRow)
			{
				continue;
			}
			if (sp->getPositionY() == plant->getImg()->getPositionY() && fabs(sp->getPositionX() - sp_plant->getPositionX())<sp->getContentSize().width / 2 * sp->getScaleX() + sp_plant->getContentSize().width / 2 * sp_plant->getScaleX() - 10)
			{
				flagin = true;
				p = plant;
			}
			if (sp->getPositionY() == plant->getImg()->getPositionY() && fabs(sp->getPositionX() - sp_plant->getPositionX()) < sp->getContentSize().width / 2 * sp->getScaleX() + sp_plant->getContentSize().width / 2 * sp_plant->getScaleX() + 10)
			{
				flagout = false;
				p = plant;
			}
		}
		if (zombie->isMeeting() && flagout) {
			std::cout << "移动" << std::endl;
			zombie->Move();
			zombie->setMeeting(false);
		}
		else if (!zombie->isMeeting() && flagin) {
			zombie->attack(p);
			zombie->setMeeting(true);
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
	for (int j = 0; j < readyZombies.size(); j++)
	{
		Zombie* zombie = readyZombies.at(j);
		Sprite* sp = zombie->getImg();
		if (zombie->getHp() <= 0)
		{
			zombie->Die();
			j--;
		}
	}
}

void EntityLayer::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}

