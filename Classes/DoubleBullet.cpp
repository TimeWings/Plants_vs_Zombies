#include "DoubleBullet.h"
#include "Global.h"
DoubleBullet::DoubleBullet(Point position):PeaBullet()
{
	Sprite *sp = Sprite::create("doubleBullet.png");
	sp->setScale(0.3);
	sp->setPosition(position.x + sp->getContentSize().width*sp->getScale() / 2, position.y);
	preBullet.insert(this, sp);
}

Sprite * DoubleBullet::attack_Animation(Sprite * sp)
{
	return NULL;
}
