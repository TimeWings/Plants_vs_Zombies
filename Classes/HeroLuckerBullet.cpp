#include "HeroLuckerBullet.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>

HeroLuckerBullet::HeroLuckerBullet(Point position, int Plant_row)
{
	this->getRange()->push_back(Plant_row);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("HeroLucker\Bramble\\bramble14.png"));
	//sp->setAnchorPoint(Point::ZERO);
	//方便以后获取子弹精灵
	this->setImg(sp);
	this->setDamage(2);
	this->getImg()->setTag(Penetrable_tag);
	sp->retain();
	sp->setScale(1.5);
	sp->setPosition(position.x, position.y - sp->getContentSize().height * sp->getScaleY() / 2);
	this->addLayer(sp);
	readyBullet.push_back(this);
	this->attack_Animation();
}

void HeroLuckerBullet::releaseZombie(Node* sPender, Zombie * zombie)
{
	zombie->getScheduler()->setTimeScale(1);
}

void HeroLuckerBullet::attack_Animation()
{
	SpriteFrame *sp;
	Sprite* bulletSprite = this->getImg();
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 11; i++)
	{
		sprintf(str, "HeroLucker\Bramble\\bramble%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	//子弹（伪）播放动画
	this->getImg()->runAction(Animate::create(an));
	//到时候植物那边会清理掉
}

void HeroLuckerBullet::Hit_Animation(Zombie * zombie)
{
	Point HitPoint = zombie->getImg()->getPosition();
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 10; i++)
	{
		sprintf(str, "HeroLucker\Blood\\blood%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("HeroLucker\Blood\\blood1.png"));
	sp->setPosition(Point(HitPoint.x, HitPoint.y));
	sp->retain();
	sp->setScale(1.4);
	EntityLayer* bl = EntityLayer::getInstance();
	bl->addChild(sp, zombie->getRow() * 3 - 1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(HeroLuckerBullet::clear, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);
	//僵尸减速
	zombie->getScheduler()->setTimeScale(0.7);
	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(HeroLuckerBullet::releaseZombie, this, zombie));
	Sequence *sequence1 = Sequence::create(CCDelayTime::create(1), actionDone, NULL);
	this->getImg()->runAction(sequence1);
}
