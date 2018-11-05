#include "Lucker.h"
#include "Global.h"
#include <iostream>

Lucker::Lucker(Point position, int row, int col)
{
	this->damage = 1;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Lucker\\lucker1.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(2);
	sp->setPosition(Point(position.x,position.y - sp->getContentSize().height * 2));
	this->setHp(10);
	this->setInterval(500);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	readyPlants.push_back(this);
}

bool Lucker::isWorking()
{
	return true;
}

void Lucker::work()
{
	stab();
}

void Lucker::Self_Animation()
{
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 19; i++)
	{
		sprintf(str, "Lucker\\lucker%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.15);
	this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
}

void Lucker::stab()
{
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		if (this->getRow() == zombie->getRow() && this->getImg()->boundingBox().intersectsRect(zombie->getImg()->getBoundingBox()) && this->getCol() == map::Point2Rank(zombie->getImg()->getPosition()).second )
		{
			//僵尸扣血
			zombie->DamageZombie(this->damage);
		}
	}
	this->setNewBirthTime();
}
