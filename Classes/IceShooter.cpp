#include "IceShooter.h"
#include "Global.h"
#include "IceBullet.h"
#include <iostream>

IceShooter::IceShooter(Point position)
{
	Sprite*sp = Sprite::create("iceShooter.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	prePlants.push_back(this);
}

void IceShooter::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 1.0f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.07f, 1.0f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.2f, 1.0f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite*sp = this->getImg();
	Point a = ccp(sp->getPositionX() + sp->getContentSize().width*sp->getScale() / 2, sp->getContentSize().height*sp->getScale() / 4 + sp->getPositionY());
	Bullet *pb = new IceBullet(a);
}
