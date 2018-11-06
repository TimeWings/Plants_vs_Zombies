#include "StarShooter.h"
#include "Global.h"
#include "PeaBulletPlus.h"
#include "MelancholyBullet.h"

StarShooter::StarShooter(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("StarShooter.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.2);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	addLayer(sp);
	this->Self_Animation();
	readyPlants.push_back(this);
}

void StarShooter::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite *sp = this->getImg();
	//植物中心点X坐标，植物中心点+1/4植物高度的Y坐标
	Point a = ccp(sp->getPositionX(),sp->getPositionY());
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double distance = sqrt(visibleSize.width*visibleSize.width + visibleSize.height*visibleSize.height);
	new PeaBulletPlus(a, this->getRow(), 30, distance);
	new PeaBulletPlus(a, this->getRow(),90, distance);
	new PeaBulletPlus(a, this->getRow(), 180, distance);
	new PeaBulletPlus(a, this->getRow(), -90, distance);
	new PeaBulletPlus(a, this->getRow(), -30, distance);
	setNewBirthTime();
}
