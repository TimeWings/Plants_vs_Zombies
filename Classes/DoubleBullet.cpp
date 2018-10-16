#include "DoubleBullet.h"
#include "Global.h"
DoubleBullet::DoubleBullet(Point position):PeaBullet()
{
	Sprite *sp = Sprite::create("doubleBullet.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position.x , position.y);
	preBullet.push_back(this);
}

Sprite * DoubleBullet::attack_Animation()
{
	return NULL;
}
