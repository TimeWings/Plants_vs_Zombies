#include "EntityLayer.h"
#include "Global.h"
#include "LadderEquip.h"
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
	this->schedule(schedule_selector(EntityLayer::Check_Lost_head_Zombie), 0.1);
	this->schedule(schedule_selector(EntityLayer::Check_Lost_Equip_Zombie), 0.1);
	this->schedule(schedule_selector(EntityLayer::Check_isAttack_Plant), 0.1);
	this->schedule(schedule_selector(EntityLayer::Check_isWorking_Zombie), 0.1);
	this->schedule(schedule_selector(EntityLayer::Check_Death), 0.1);
	this->schedule(schedule_selector(EntityLayer::Check_Zombie_Climb), 0.1);
	this->schedule(schedule_selector(EntityLayer::showInfo), 0.1);
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
				if (strcmp(typeid(*zombie).name(), "class PoleVaultingZombie") == 0)
				{
					Vec2 pointA=sp->getPosition();
					Vec2 pointB=zombie->getImg()->getPosition();
					float distance = sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2));
					if (distance > BlockSize.first*0.5)
					{
						continue;
					}
				}
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
				if (strcmp(typeid(*bullet).name(), "class HeroLuckerBullet") != 0 && strcmp(typeid(*bullet).name(), "class MushroomBullet") != 0)
				{
					break;
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
			Plants *plant = NULL;
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
			if (plant != NULL)
			{
				plant->setBirthTime(seconds);
			}
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
void EntityLayer::Check_isWorking_Zombie(float t)
{
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* x = readyZombies.at(i);
		struct timeb t1;
		ftime(&t1);
		long long seconds = t1.time * 1000 + t1.millitm;
		long long interval = seconds - x->getBirthTime();
		//long long a = (interval / 100L) * 100;
		if (interval > x->getInterval()) {
			//调用工作函数
			x->setNewBirthTime();
			x->work();
		}
	}
}
void EntityLayer::Check_isAttack_Zombie(float t)
{
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie *zombie = readyZombies.at(i);
		bool jump = false;
		if (!zombie->hasHead()) jump = true;
		for (auto i : *(zombie->getDebuff())) {
			if (i == Freezing || i == DrivingOut||i== Jumping_Tag||i== Climb_Tag) {
				jump = true;
				break;
			}
		}
		if (jump) continue;
		Sprite *sp = zombie->getImg();
		PlantStatus *p;
		bool flag = false;
		double zombiex = sp->getPositionX();
		std::pair<int, int> zombie_rank = std::make_pair(zombie->getRow(), Point2Rank(sp->getPosition()).second);
		double plantx = Rank2Point(zombie_rank.first, zombie_rank.second).x;
		if (strcmp(typeid(*zombie).name(), "class Gargantuar") == 0) {
			PlantStatus *ps = map::find(zombie_rank.first, zombie_rank.second);
			if (ps == nullptr || ps->plantVector.size() == 0) {
				ps = map::find(zombie_rank.first, zombie_rank.second - 1);
			}
			if (ps != nullptr && ps->plantVector.size() > 0) {
				flag = true;
				p = ps;
			}
		}
		else if (strcmp(typeid(*zombie).name(), "class MinerZombie") == 0) {
			if (zombiex <= plantx) {
				PlantStatus *ps = map::find(zombie_rank.first, zombie_rank.second);
				if (ps != nullptr && ps->plantVector.size() > 0 && strcmp(typeid(*(ps->plantVector.at(0))).name(), "class Lucker") != 0 && strcmp(typeid(*(ps->plantVector.at(0))).name(), "class Tomb") != 0 && strcmp(typeid(*(ps->plantVector.at(0))).name(), "class Ladder") != 0) {
					flag = true;
					p = ps;
				}
			}
		}
		else if (zombiex >= plantx) {
			PlantStatus *ps = map::find(zombie_rank.first, zombie_rank.second);
			if (ps != nullptr && ps->plantVector.size() > 0 && strcmp(typeid(*(ps->plantVector.at(0))).name(), "class Lucker") != 0 && strcmp(typeid(*(ps->plantVector.at(0))).name(), "class Tomb") != 0 && strcmp(typeid(*(ps->plantVector.at(0))).name(), "class Ladder") != 0){
				flag = true;
				p = ps;
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

void EntityLayer::Check_Lost_Equip_Zombie(float t) {
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie *zombie = readyZombies.at(i);
		if (zombie->hasEquip() && zombie->getEquip()->getHp() <= 0) {
			/*zombie->getEquip()->getImg()->removeFromParent();
			zombie->setEquip(nullptr);
			if (zombie->hasHead()) {
				zombie->setMeeting(false);
				zombie->Move();
			}*/
			zombie->Lost_Equip();
		}
	}
}
void EntityLayer::Check_Zombie_Climb(float t)
{
	for (auto x : readyZombies)
	{
		if (strcmp(typeid(*x).name(), "class MinerZombie") == 0|| strcmp(typeid(*x).name(), "class Gargantuar") == 0)
		{
			continue;
		}
		bool climb = false;
		for (auto z : *(x->getDebuff()))
		{
			if (z == Climb_Tag)
			{
				climb = true;
				break;
			}
		}
		if (climb)continue;
		for (auto y : LadderEquip::LadderSprite)
		{
			if (x->getRow() == map::Point2Rank(y->getPosition()).first&&x->getImg()->getBoundingBox().intersectsRect(y->getBoundingBox())&&x->getImg()->getPositionX()>y->getPositionX())
			{
				x->Climb_Animation(y);
			}
		}
	}
}
void EntityLayer::Check_Death(float t)
{
	for (int i = 0; i < plantstatus.size(); i++)
	{
		for (int j = 0; j < plantstatus.at(i)->plantVector.size(); j++)
		{
			
			if (plantstatus.at(i)->plantVector.at(j)->getHp() <= 0)
			{
				RemoveRegister(plantstatus.at(i)->plantVector.at(j));
				j--;
			}
		}
	}
}

void EntityLayer::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}

void EntityLayer::showInfo(float t)
{
	std::cout << "子弹容量：" << readyBullet.size() << std::endl;
	std::cout << "植物容量：" << readyPlants.size() << std::endl;
	std::cout << "僵尸容量：" << readyZombies.size() << std::endl;
	std::cout << "格子状态容量：" << plantstatus.size() << std::endl;
	

}

