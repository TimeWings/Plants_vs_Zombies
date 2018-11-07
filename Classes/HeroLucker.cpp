#include "HeroLucker.h"
#include "Global.h"
#include "HeroLuckerBullet.h"
#include <iostream>

HeroLucker::HeroLucker(Point position, int row, int col)
{
	this->position = position;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("HeroLucker\\HeroLucker.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(8000);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

void HeroLucker::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
}

void HeroLucker::CreateBullet()
{
	//播放产生子弹的动画
	CCScaleBy * scaleup = CCScaleBy::create(0.1f, 0.8f, 0.8f);
	CCScaleBy * scaledown = CCScaleBy::create(0.1f, 1.5625f, 1.5625f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 0.8f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		Point a = zombie->getImg()->getPosition();
		HeroLuckerBullet *pb = new HeroLuckerBullet(a, zombie->getRow());
	}
	setNewBirthTime();
}

void HeroLucker::Self_Animation()
{
	//Q弹效果
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(0.7f, preScale, preScale + 0.05);
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale, preScale);
	Sequence *sequence1 = Sequence::create(scaleup, scaledown, NULL);
	CCActionInterval * moveBy = CCMoveBy::create(1, ccp(7, 0));
	CCActionInterval * actionmoveback = moveBy->reverse();
	CCFiniteTimeAction * spawn1 = CCSpawn::create(sequence1, moveBy, NULL);
	CCFiniteTimeAction * spawn2 = CCSpawn::create(sequence1, actionmoveback, NULL);
	Sequence *sequence2 = Sequence::create(spawn1, spawn2, NULL);
	sp->runAction(CCRepeatForever::create(sequence2));
}

void HeroLucker::clearBullet(Node * pSender, HeroLuckerBullet * bp)
{
	//消除子弹
	bp->getImg()->removeFromParent();
	bp->clear(bp->getImg());
	//设置时间
	this->setNewBirthTime();
}
