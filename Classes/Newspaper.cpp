#include "Newspaper.h"
#include "Zombie.h"

Newspaper::Newspaper()
{
	setHp(12);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\NewspaperZombie\\Newspaper\\Newspaper.png"));
	sp->retain();
	this->setImg(sp);
}

void Newspaper::Move()
{
	NewspaperMove();
}

void Newspaper::NewspaperMove()
{
	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\NewspaperZombie\\Newspaper\\Walkgif\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 19; i++)
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

void Newspaper::Attack(double interval)
{
	NewspaperAttack(interval);
}

void Newspaper::NewspaperAttack(double interval)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\NewspaperZombie\\Newspaper\\Attackgif\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 8; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, interval);
	CCRepeatForever *rf = CCRepeatForever::create(Animate::create(an));
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}
