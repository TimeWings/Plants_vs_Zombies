#include "DoorZombie.h"
#include "Global.h"
#include <iostream>

DoorZombie::DoorZombie()
{
}

DoorZombie::DoorZombie(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);

	setWalkSpeed(7);
	setHp(12);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\DoorZombie\\DoorZombie.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	setEquip(new Door());
	getEquip()->getImg()->setPosition(sp->getContentSize().width/2, sp->getContentSize().height/2);
	sp->addChild(getEquip()->getImg());
	this->setSche(sp);
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}

void DoorZombie::Attack(PlantStatus * plantstatus)
{
	if (!hasHead()) return;
	Stop_Animation();
	if (hasEquip())
	{
		DoorAttack(plantstatus);
		getEquip()->Attack();
	}
	else
	{
		BasicAttack(plantstatus);
	}
}

void DoorZombie::DoorAttack(PlantStatus * plantstatus)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr;
	CCRepeatForever *rf;

	prestr = "Zombies\\DoorZombie\\Attackgif\\";

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

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, Animate::create(an1), actionDone, NULL);
	rf = CCRepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void DoorZombie::Move()
{
	if (!hasHead()) return;
	Stop_Animation();
	if (hasEquip())
	{
		DoorMove();
		getEquip()->Move();
	}
	else
	{
		BasicMove();
	}
}

void DoorZombie::DoorMove()
{
	Sprite *sp = this->getImg();
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	std::cout << distance << " " << getPreWalkSpeed() << std::endl;
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);

	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Die, this));
	CCSequence *sequence = CCSequence::create(moveTo, scaledown, actionDone, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);

	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\DoorZombie\\Walkgif\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 23; i++)
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

void DoorZombie::DamageBoth(int damage)
{
	if (hasEquip()) {
		getEquip()->Damage(damage);
	}
	DamageZombie(damage);
}

void DoorZombie::DamageEquip(int damage)
{
	if (hasEquip()) {
		std::cout << "ÃÅÊÜµ½¹¥»÷" << std::endl;
		getEquip()->Damage(damage);
	}
	else {
		DamageZombie(damage);
	}
}

void DoorZombie::DamageZombie(int damage)
{
	std::cout << "fuck" << std::endl;
	setHp(getHp() - damage);
	Attacked();
}

Sprite * DoorZombie::MagnetEquip()
{
	if (!hasEquip())
		return nullptr;
	getEquip()->setHp(0);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\DoorZombie\\Door\\Door.png"));
	sp->setScale(this->getImg()->getScaleX());
	sp->setPosition(this->getImg()->getPosition());
	addLayer(sp);
	return sp;
}