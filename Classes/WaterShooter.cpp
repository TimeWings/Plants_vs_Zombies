#include "WaterShooter.h"
#include "WaterBullet.h"
#include "Global.h"

WaterShooter::WaterShooter(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("WaterShooter\\WaterShooter.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.25);
	sp->setPosition(position);
	this->setHp(5);
	this->setInterval(2000);
	this->addLayer(sp);
	this->Self_Animation();
	readyPlants.push_back(this);
}

void WaterShooter::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	this->getImg()->removeFromParent();
}

void WaterShooter::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite*sp = this->getImg();
	Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	Bullet *pb = new WaterBullet(a, this->getRow());
	setNewBirthTime();
}
