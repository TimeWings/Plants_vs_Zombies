#include "Clover.h"
#include "Global.h"
#include "Background.h"
#include <iostream>
Clover::Clover(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Card\\Clover.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(2.5);
	sp->setPosition(position);
	this->setHp(2000);
	this->setInterval(0);
	addLayer(sp);
	readyPlants.push_back(this);
}

bool Clover::isWorking()
{
	if (isBlowing)
	{
		return false;
	}
	return true;
}

void Clover::work()
{
	if (isWorking())
	{
		std::cout << "´µÑ½´µÑ½,ÎÒµÄ½¾°Á·Å×Ý!!!" << std::endl;
		isBlowing = true;
		char str[100] = { 0 };
		Vector<SpriteFrame*> allframe;
		for (int i = 1; i <= 3; i++)
		{
			sprintf(str, "Clover\\Blow\\%d.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Vector<SpriteFrame*> allframe1;
		for (int i = 1; i <= 30; i++)
		{
			sprintf(str, "Clover\\Self_Animation\\%d.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe1.pushBack(frame);
		}
		Animation* anSelf = Animation::createWithSpriteFrames(allframe1, 0.05);
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.07);
		Repeat* an1 = Repeat::create(Animate::create(an), 10);
		auto Blowing = CallFuncN::create(CC_CALLBACK_1(Clover::Blow, this));
		Spawn* spanw = Spawn::create(an1, Blowing, NULL);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(Clover::readyDie, this));
		Sequence *sequence = Sequence::create(Animate::create(anSelf), spanw, actionDone, NULL);
		this->getImg()->runAction(sequence);
	}
}
void Clover::Blow(Node * pSender)
{
	auto cloud = Background::Cloud;
	if (cloud == NULL)
	{
		return;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double distance = (visibleSize.width + cloud->getContentSize().width*cloud->getScaleX() - cloud->getPositionX()) / 15;
	double time = distance / 12;
	MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width + cloud->getContentSize().width/2*cloud->getScaleX(), cloud->getPosition().y));
	MoveTo *comeBack = MoveTo::create(time, Vec2(visibleSize.width/2, visibleSize.height/2));
	Sequence *sequence = Sequence::create(moveTo, DelayTime::create(5),comeBack, NULL);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(cloud);
	cloud->runAction(sequence);

}
void Clover::readyDie(Node * pSender)
{
	this->setHp(0);
}

void Clover::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}
