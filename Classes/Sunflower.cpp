#include "Sunflower.h"
#include "Global.h"
#include "UILayer.h"
#include <time.h>
#include <iostream>
#include <sys/timeb.h>
Sunflower::Sunflower(Point position,int row,int col)
{
	//std::cout << "Ì«Ñô»¨Éú³É" << std::endl;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("sunFlower.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(2);
	this->setInterval(5000);
	addLayer(sp);
	this->Self_Animation();
	readyPlants.push_back(this);
}

void Sunflower::work()
{
	CreateSun();
}

void Sunflower::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

void Sunflower::Self_Animation()
{
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(0.7f, preScale, preScale + 0.05);
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale, preScale);
	Sequence *sequence1 = Sequence::create(scaleup, scaledown, NULL);
	CCActionInterval * moveBy = CCMoveBy::create(1, ccp(8, 0));
	CCActionInterval * actionmoveback = moveBy->reverse();
	CCFiniteTimeAction * spawn1 = CCSpawn::create(sequence1, moveBy, NULL);
	CCFiniteTimeAction * spawn2 = CCSpawn::create(sequence1, actionmoveback, NULL);
	Sequence *sequence2 = Sequence::create(spawn1, spawn2, NULL);
	sp->runAction(CCRepeatForever::create(sequence2));
}

void Sunflower::CreateSun()
{
	Sprite * sp = this->getImg();
	if (readySun.find(sp) != readySun.end())
	{
		return;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto spSun = Sprite::createWithTexture(TextureCache::getInstance()->addImage("sun.png"));
	Point a = Point(sp->getPositionX(), sp->getPositionY() + sp->getContentSize().height / 2 * sp->getScaleY());
	spSun->setPosition(a);
	spSun->setScale(0.5);
	UILayer::getInstance()->addChild(spSun, 202);

	Point b = Point(sp->getPositionX() - sp->getContentSize().width / 2 * sp->getScaleX() - spSun->getContentSize().width / 2 * spSun->getScale(), sp->getPositionY());
	float height = sp->getContentSize().height / 2 * sp->getScaleX();
	CCActionInterval * jumpto = CCJumpTo::create(1, b, height, 1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Sunflower::clearSun, this, sp));
	CCFiniteTimeAction * reveseseq = CCSequence::create(jumpto, CCDelayTime::create(3.2), actionDone, NULL);
	spSun->runAction(reveseseq);
	readySun.insert(sp, spSun);
	setNewBirthTime();
}

bool Sunflower::isWorking()
{
	return false;
}

void Sunflower::clearSun(Node *pSender, Sprite *sunFlower)
{
	Plants *plant=NULL;
	for (auto x : readyPlants)
	{
		if (x->getImg() == sunFlower)
		{
			plant = x;
		}
	}

	struct timeb t1;
	ftime(&t1);
	long long seconds = t1.time * 1000 + t1.millitm;
	if(plant!=NULL)
	plant->setBirthTime(seconds);
	pSender->removeFromParent();
	readySun.erase(sunFlower);
}




