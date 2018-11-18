#include "LadderEquip.h"
Vector<Sprite*> LadderEquip::LadderSprite;
LadderEquip::LadderEquip()
{
	setHp(50);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("none.png"));
	sp->retain();
	this->setImg(sp);
}

void LadderEquip::Die()
{
}

void LadderEquip::Damage(int damage)
{
	setHp(getHp() - damage);
}

void LadderEquip::Move()
{
}

void LadderEquip::Attack(double interval)
{
}
