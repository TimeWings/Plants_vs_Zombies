#include "RoadblockZombie.h"
#include "Global.h"
#include <iostream>

RoadblockZombie::RoadblockZombie()
{
}

RoadblockZombie::RoadblockZombie(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	setEquip(new Roadblock());
	setWalkSpeed(7);
	setHp(12);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\BasicZombie\\BasicZombie.png"));
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}

void RoadblockZombie::Attack(Plants *plant)
{
	Sprite *sp = this->getImg();
	if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
		sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
	if (hasEquip())
	{
		RoadblockAttack(plant);
	}
	else
	{
		BasicAttack(plant);
	}
}

void RoadblockZombie::RoadblockAttack(Plants * plant)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr;
	CCRepeatForever *rf;

	prestr = "Zombies\\RoadblockZombie\\Attackgif\\";

	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 6; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	for (int i = 7; i <= 11; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an1 = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Damage, this, plant));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, Animate::create(an1), actionDone, NULL);
	rf = CCRepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void RoadblockZombie::Move()
{
	Sprite *sp = this->getImg();
	if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
	{
		sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
	}
	if (hasEquip()) 
	{
		RoadblockMove();
	}
	else 
	{
		BasicMove();
	}
}

void RoadblockZombie::RoadblockMove()
{
	Sprite *sp = this->getImg();
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	//std::cout << distance << " " << getPreWalkSpeed() << std::endl;
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);

	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	CCSequence *sequence = CCSequence::create(moveTo, scaledown, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);

	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\RoadblockZombie\\Walkgif\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 21; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.12);
	CCRepeatForever *rf = CCRepeatForever::create(Animate::create(an));
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void RoadblockZombie::DamageBoth(int damage)
{
	DamageEquip(damage);
}

void RoadblockZombie::DamageEquip(int damage)
{
	if (hasEquip()) {
		getEquip()->Damage(damage);
		std::cout << getEquip()->getHp() << std::endl;
	}
	else {
		setHp(getHp() - damage);
	}
	Attacked();
}
