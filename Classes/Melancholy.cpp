#include "Melancholy.h"
#include "Global.h"
#include "MelancholyBullet.h"

Melancholy::Melancholy(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Melancholy.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.2);
	sp->setPosition(position);
	this->setHp(6);
	addLayer(sp);
	this->setInterval(1000);
	this->Self_Animation();
	distance = map::BlockSize.first*1.5;
	readyPlants.push_back(this);
}
bool Melancholy::isWorking()
{
	for (auto x : readyZombies)
	{
		Sprite *sp = x->getImg();
		double x1 = this->getImg()->getPositionX();
		double x2 = sp->getPositionX();
		double y1 = this->getImg()->getPositionY();
		double y2 = sp->getPositionY();
		double curdis = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
		if (curdis <= distance)
		{
			return true;
		}
	}
	return false;
}

void Melancholy::work()
{
	if (isWorking())
	{
		CreateBullet();
	}
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
