#include "Thunder.h"
#include "Global.h"
#include "Math.h"
#include <iostream>
#include <algorithm>
#include "sys/timeb.h"
Thunder::Thunder()
{
}
Thunder::Thunder(Point position, int row, int col)
{
	this->hasThunder = false;
	this->curtentDamage = 3;
	this->thunderHeight = 1.5;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Thunder\\thunder.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.25);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	this->Self_Animation();
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
	this->lastPoint = this->getImg()->getPosition();
}

bool Thunder::isWorking()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto x : readyZombies)
	{
		if (this->getRow() == x->getRow() && x->getImg()->getPositionX() < visibleSize.width)
		{
			return true;
		}
	}
	return false;
}

void Thunder::work()
{
	if (isWorking())
	{
		creatSprite();
	}
}

void Thunder::creatSprite()
{
	//找出同行僵尸
	std::vector<Zombie*> zombieSet;
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		if (zombie->getRow() == this->getRow() && zombie->getImg()->getPositionX() >= this->getImg()->getPositionX())
		{
			zombieSet.push_back(zombie);
		}
	}
	//按照X轴排序
	std::vector<Zombie*> zombieSetSorted;
	Zombie* min;
	int NO;
	for (int i = 0; i < zombieSet.size();)
	{
		Zombie* zombie = zombieSet.at(i);
		min = zombie;
		NO = 0;
		for (int j = 1; j < zombieSet.size(); j++)
		{
			if (min->getCol() > zombieSet.at(j)->getCol())
			{
				min = zombieSet.at(j);
				NO = j;
			}
		}
		zombieSetSorted.push_back(min);
		zombieSet.erase(zombieSet.begin() + NO);
	}
	

	for (int i = 0; i < zombieSetSorted.size() && curtentDamage > 0; i++)
	{
		Zombie* zombie = zombieSetSorted.at(i);
		if (zombie->getImg()->getPositionX() >= this->getImg()->getPositionX())
		{
			if (!this->hasThunder)
			{
				this->hasThunder = true;
				std::cout << this->getImg()->getPosition().x + this->getImg()->getContentSize().width * this->getImg()->getScaleX() / 2.5 << " " << this->getImg()->getPositionY() + this->getImg()->getContentSize().height * this->getImg()->getScaleY() / 2 << std::endl;
				createThunder(
					Point(this->getImg()->getPosition().x + this->getImg()->getContentSize().width * this->getImg()->getScaleX() / 2.5 , this->getImg()->getPositionY() + this->getImg()->getContentSize().height * this->getImg()->getScaleY() / 2), 
					Point(zombie->getImg()->getPosition().x, zombie->getImg()->getPosition().y), 
					zombie);
			}
			else
			{
				createThunder(this->lastPoint, zombie->getImg()->getPosition(), zombie);
			}
			this->lastPoint = zombie->getImg()->getPosition();
		}
		zombie->DamageBoth(curtentDamage--);
	}
	this->curtentDamage = 3;
	this->lastPoint = this->getImg()->getPosition();
	this->hasThunder = false;
	setNewBirthTime();
}

void Thunder::createThunder(Point startPoint, Point endPoint, Zombie* zombie)
{
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str, "Thunder\\thunder%d.png", i);
		//一定用这种加载方法
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Thunder\\thunder1.png"));
	sp->setPosition(
		Point(
		fabs(endPoint.x - startPoint.x) / 2 + (startPoint.x < endPoint.x ? startPoint.x : endPoint.x),
		fabs(startPoint.y - endPoint.y) / 2 + (startPoint.y < endPoint.y ? startPoint.y : endPoint.y)
		));
	sp->retain();

	sp->setScaleX(sqrt(pow(startPoint.x - endPoint.x, 2) + pow(startPoint.y - endPoint.y, 2)) / sp->getContentSize().width );
	sp->setScaleY(thunderHeight);

	//旋转
	if(startPoint.y != endPoint.y)
	{
		sp->setRotation(atan2(startPoint.y - endPoint.y, endPoint.x - startPoint.x) * 180 / 3.1415926);
	}
	EntityLayer* bl = EntityLayer::getInstance();
	bl->addChild(sp, zombie->getRow() * 3 - 2);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaShooter::clear, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);
	
	//僵尸被雷击中效果
	CCActionInterval * tintto1 = CCTintTo::create(0.1, 0, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.1, 255,255,255);
	Sequence *sequence1 = Sequence::create(tintto1, tintto2, NULL);
	Sequence *sequence2 = Sequence::create(sequence1, sequence1, sequence1, NULL);
	zombie->getImg()->runAction(sequence2);

}
