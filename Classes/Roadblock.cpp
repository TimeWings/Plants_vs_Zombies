#include "Roadblock.h"

Roadblock::Roadblock()
{
	setHp(12);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("none.png"));
	this->setImg(sp);
}

void Roadblock::Die()
{
}

void Roadblock::Damage(int damage)
{
	setHp(getHp() - damage);
}

void Roadblock::Move()
{
}

void Roadblock::Attack()
{
}
