#include "PeaShooter.h"
#include "PeaBullet.h"
#include "Global.h"

PeaShooter::PeaShooter(Point position) {
	
	Sprite*sp = Sprite::create("peaShooter.png");
	setScale(0.3);
	sp->setScale(getScale());
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(500);
	prePlants.insert(this, sp);

}
void PeaShooter::Attack()
{

}

void PeaShooter::Die()
{
}

void PeaShooter::Self_Animation(Sprite *sp)
{
	ScaleBy * scaledown = ScaleBy::create(1.0f, 0.5f, 0.5f);
	ScaleBy * scaleup = ScaleBy::create(1.0f, 2.0f, 2.0f);
	Sequence *sequence = Sequence::create(scaledown, scaleup, NULL);
	sp->runAction(RepeatForever::create(sequence));
}

void PeaShooter::Attack_Animation(Sprite*sp)
{
}

void PeaShooter::Attacked()
{
}

bool PeaShooter::isAttacking()
{
	return false;
}

void PeaShooter::CreateBullet(Sprite *sp)
{
	Bullet *pb = new PeaBullet(Point(sp->getPositionX()+sp->getContentSize().width / 2, sp->getContentSize().height / 2 + sp->getPositionY() / 2));
}

