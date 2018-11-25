#include "HeroLuckerBullet.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>

HeroLuckerBullet::HeroLuckerBullet(Point position, int Plant_row)
{
	this->row = Plant_row;
	this->getRange()->push_back(Plant_row);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("HeroLucker\\Bramble\\bramble14.png"));
	//sp->setAnchorPoint(Point::ZERO);
	//方便以后获取子弹精灵
	this->setImg(sp);
	this->setDamage(1);
	this->getImg()->setTag(Penetrable_tag);
	sp->retain();
	sp->setScale(1.5);
	sp->setPosition(position.x, position.y);
	this->addLayer(sp);
	readyBullet.push_back(this);
	this->attack_Animation();
}

void HeroLuckerBullet::releaseZombie(Node* sPender, Zombie * zombie)
{
	if (zombie != NULL)
	{
		return;
	}
	for (int i = 0; i < zombie->getDebuff()->size(); i++)
	{
		if (zombie->getDebuff()->at(i) == Stick)
		{ 
			zombie->getDebuff()->erase(zombie->getDebuff()->begin() + i);
			break;
		}
	}
	zombie->getScheduler()->setTimeScale(1);
}

void HeroLuckerBullet::attack_Animation()
{
	Sprite* bulletSprite = this->getImg();
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 14; i++)
	{
		sprintf(str, "HeroLucker\\Bramble\\bramble%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	//子弹（伪）播放动画
	this->getImg()->runAction(Animate::create(an));
	//子弹持续2秒消除
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(HeroLuckerBullet::clear, this));
	Sequence *sequence1 = Sequence::create(CCDelayTime::create(20), actionDone, NULL);
	this->getImg()->runAction(sequence1);
}

void HeroLuckerBullet::Hit_Animation(Zombie * zombie)
{
	for (int i = 0; i < zombie->getDebuff()->size(); i++)
	{
		if (zombie->getDebuff()->at(i) == Stick)
		{
			return;
		}
	}
	zombie->getDebuff()->push_back(Stick);
	Point HitPoint = zombie->getImg()->getPosition();
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 11; i++)
	{
		sprintf(str, "HeroLucker\\Blood\\blood%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.2);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("HeroLucker\\Blood\\blood1.png"));
	sp->setPosition(Point(HitPoint.x, HitPoint.y));
	sp->retain();
	sp->setScale(1);
	EntityLayer* bl = EntityLayer::getInstance();
	bl->addChild(sp, zombie->getRow() * 3 - 1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(HeroLuckerBullet::clearSprite, this, sp));
	Sequence *sequence = Sequence::create(Animate::create(an), CCDelayTime::create(2), actionDone, NULL);
	sp->runAction(sequence);
	//僵尸减速
	zombie->getScheduler()->setTimeScale(0.7);
	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(HeroLuckerBullet::releaseZombie, this, zombie));
	//僵尸减速持续时间
	Sequence *sequence1 = Sequence::create(CCDelayTime::create(1), actionDone1, NULL);
	this->getImg()->runAction(sequence1);
}

void HeroLuckerBullet::clear(Node * pSender)
{
	std::cout << "清除子弹" << std::endl;
	pSender->removeFromParent();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
}

void HeroLuckerBullet::clearSprite(Node * pSender, Sprite * sp)
{
	std::cout << "消除流血特效" << std::endl;
	sp->removeFromParent();
}
