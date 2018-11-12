#include "Bucket.h"

Bucket::Bucket()
{
	setHp(36);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("none.png"));
	sp->retain();
	this->setImg(sp);
}
