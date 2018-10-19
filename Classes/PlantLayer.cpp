#include "PlantLayer.h"
#include "Global.h"
#include "Entity.h"
#include "PeaShooter.h"
#include <iostream>
#include "Plants.h"
#include <stdio.h>
#include <math.h>
#include <sys/timeb.h>
#include <time.h>
PlantLayer* PlantLayer::pRet = NULL;
PlantLayer* PlantLayer::create()
{
	PlantLayer ::pRet = new PlantLayer();
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
bool PlantLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Point touchPos = touch->getLocation();
	for (auto x : readySun.keys())
	{
		Sprite *sun = readySun.at(x);
		if (touchPos.x > sun->getPositionX() - sun->getContentSize().width / 2 * sun->getScale()&&touchPos.x < sun->getPositionX() + sun->getContentSize().width / 2 * sun->getScale()
			&&touchPos.y< sun->getPositionY() + sun->getContentSize().height / 2 * sun->getScale()&&touchPos.y>sun->getPositionY() - sun->getContentSize().height / 2 * sun->getScale())
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
			MoveTo *moveTo = MoveTo::create(2, ccp(sunCnt.second.first  ,sunCnt.second.second));
			CCActionInterval * rotate = CCRotateTo::create(2, 180);
			CCFiniteTimeAction * spawn = CCSpawn::create(moveTo, rotate, NULL);
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(PlantLayer::clearNode,this));
			CCFiniteTimeAction * reveseseq = CCSequence::create(spawn, actionDone, NULL);
			sun->runAction(reveseseq);
			readySun.erase(x);
		}
	}
	return false;
}
void PlantLayer::onTouchEened(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
}
bool PlantLayer::init() {
	//这里写时间定时器
	this->setTouchEnabled(true);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PlantLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlantLayer::onTouchEnded, this);
	listener->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->schedule(schedule_selector(PlantLayer::Check_isAttack), 0.1);
	return true;
}

void PlantLayer::Check_isAttack(float t)
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
			x->work();
			struct timeb t1;
			ftime(&t1);
			long long seconds = t1.time * 1000 + t1.millitm;
			x->setBirthTime(seconds);
		}
	}
}
void PlantLayer::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}
//void PlantLayer::Produce_Sun(float t)
//{
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	for (auto x : preSun.keys())
//	{
//		Sprite* sun = preSun.at(x);
//		this->addChild(sun);
//		//std::cout << "太阳生成" << std::endl;
//		Point a = Point(x->getPositionX() - x->getContentSize().width / 2 * x->getScaleX() - sun->getContentSize().width / 2 * sun->getScale(), x->getPositionY());
//		float height = x->getContentSize().height/2*x->getScaleX();
//		CCActionInterval * jumpto = CCJumpTo::create(1, a, height, 1);
//		auto actionDone = CallFuncN::create(CC_CALLBACK_1(PlantLayer::clear1, this,x));
//		CCFiniteTimeAction * reveseseq = CCSequence::create(jumpto, CCDelayTime::create(3.2), actionDone, NULL);
//		sun->runAction(reveseseq);
//		readySun.insert(x, sun);
//		preSun.erase(x);
//	}
//}

