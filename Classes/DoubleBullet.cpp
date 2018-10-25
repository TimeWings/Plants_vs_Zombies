#include "DoubleBullet.h"
#include "Global.h"
DoubleBullet::DoubleBullet(Point position,int Plant_row):PeaBullet()
{
	this->getRange()->push_back(Plant_row);
	this->setDamage(1);
	this->setSpeed(6);
	Sprite *sp = Sprite::create("doubleBullet.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position.x , position.y);
	addLayer(sp);
	this->move();
	readyBullet.push_back(this);
}

