#include "Door.h"
#include <iostream>
#include "Zombie.h"

Door::Door()
{
	setHp(36);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\DoorZombie\\Door\\Door.png"));
	this->setImg(sp);
}

void Door::Die()
{

}

void Door::Damage(int damage)
{
	setHp(getHp() - damage);
	std::cout << getHp() << std::endl;
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

void Door::Move()
{
	DoorMove();
}

void Door::DoorMove() 
{
	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\DoorZombie\\Door\\Walkgif\\";
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

void Door::Attack()
{
	DoorAttack();
}

void Door::DoorAttack() 
{
	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\DoorZombie\\Door\\Attackgif\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 12; i++)
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