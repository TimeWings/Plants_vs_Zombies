#include "MinerCap.h"

MinerCap::MinerCap()
{
	setHp(20);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("none.png"));
	sp->retain();
	this->setImg(sp);
}

void MinerCap::Damage(int damage)
{
	setHp(getHp() - damage);
}
