#include "Melancholy.h"
#include "Global.h"
#include "MelancholyBullet.h"

Melancholy::Melancholy(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	Sprite*sp = Sprite::create("StarShooter.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.2);
	sp->setPosition(position);
	this->setHp(6);
	addLayer(sp);
	this->setInterval(1000);
	this->Self_Animation();
	readyPlants.push_back(this);
}

void Melancholy::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite *sp = this->getImg();
	//植物中心点X坐标，植物中心点+1/4植物高度的Y坐标
	Point a = ccp(sp->getPositionX(), sp->getPositionY());
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double distance = map::BlockSize.first;
	new MelancholyBullet(a, this->getRow(), 45, distance);
	new MelancholyBullet(a, this->getRow(), 90, distance);
	new MelancholyBullet(a, this->getRow(), 135, distance);
	new MelancholyBullet(a, this->getRow(), 180, distance);
	new MelancholyBullet(a, this->getRow(), -135, distance);
	new MelancholyBullet(a, this->getRow(), -90, distance);
	new MelancholyBullet(a, this->getRow(), -45, distance);
	new MelancholyBullet(a, this->getRow(), 0, distance);
	setNewBirthTime();
}
