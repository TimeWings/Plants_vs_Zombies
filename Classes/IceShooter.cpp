#include "IceShooter.h"
#include "Global.h"
#include "IceBullet.h"
#include <iostream>
IceShooter::IceShooter()
{
}

IceShooter::IceShooter(Point position,int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("iceShooter.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.27);
	sp->setPosition(position);
	this->setHp(3);
	this->setInterval(2000);
	this->addLayer(sp);
	this->Self_Animation();
	readyPlants.push_back(this);
}

void IceShooter::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	Sprite * sp = this->getImg();
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(IceShooter::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void IceShooter::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite*sp = this->getImg();
	Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	Bullet *pb = new IceBullet(a, this->getRow());
	setNewBirthTime();
}

void IceShooter::clear(Node * pSender)
{
	pSender->removeFromParent();
	pSender->removeAllChildrenWithCleanup(true);
}
