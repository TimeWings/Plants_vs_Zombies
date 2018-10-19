#include "DoubleBullet.h"
#include "Global.h"
DoubleBullet::DoubleBullet(Point position):PeaBullet()
{
	this->setDamage(20);
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

