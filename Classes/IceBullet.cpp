#include "IceBullet.h"
#include "Global.h"

IceBullet::IceBullet(Point position)
{
	Sprite *sp = Sprite::create("sword1.png");
	sp->setScale(0.15);
	sp->setPosition(position.x + sp->getContentSize().width*sp->getScale() / 2, position.y);
	preBullet.insert(this, sp);
}

void IceBullet::work(Sprite * sp)
{
	Self_Animation(sp);
}

void IceBullet::Hit_Animation(Sprite * sp)
{
}

Sprite * IceBullet::attack_Animation(Sprite * sp)
{
	return NULL;
}

void IceBullet::Self_Animation(Sprite * sp)
{
	ActionInterval * rotateto = RotateBy::create(0.5, 180);
    sp->runAction(RepeatForever::create(rotateto));
}
