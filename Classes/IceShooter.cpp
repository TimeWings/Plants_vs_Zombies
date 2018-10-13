#include "IceShooter.h"
#include "Global.h"
#include "IceBullet.h"
#include <iostream>

IceShooter::IceShooter(Point position)
{
	Sprite*sp = Sprite::create("iceShooter.png");
	setScale(0.3);
	sp->setScale(getScale());
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	prePlants.insert(this, sp);
}

void IceShooter::CreateBullet(Sprite * sp)
{
	//std::cout<<sp << "ÉÁÉÁµÄ½£Éú³É" << std::endl;
	Point a = ccp(sp->getPositionX() + sp->getContentSize().width*sp->getScale() / 2, sp->getContentSize().height*sp->getScale() / 4 + sp->getPositionY());
	Bullet *pb = new IceBullet(a);
}
