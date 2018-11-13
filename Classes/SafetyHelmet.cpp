#include "SafetyHelmet.h"

SafetyHelmet::SafetyHelmet()
{
	setHp(50);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("none.png"));
	sp->retain();
	this->setImg(sp);
}

void SafetyHelmet::Die()
{
}

void SafetyHelmet::Damage(int damage)
{
	setHp(getHp() - damage);
}

void SafetyHelmet::Move()
{
}

void SafetyHelmet::Attack(double interval)
{
}
