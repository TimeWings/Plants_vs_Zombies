#include "Weeds.h"
#include "Global.h"
#include "TrackBullet.h"
#include <iostream>
Weeds::Weeds(Point position,int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Weeds.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.25);
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	this->addLayer(sp);
	this->Self_Animation();
	readyPlants.push_back(this);
}

void Weeds::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite*sp = this->getImg();
	Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	Bullet *pb = new TrackBullet(a,this->getRow());
	setNewBirthTime();
}
