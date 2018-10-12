#include "PeaShooter.h"
#include "PeaBullet.h"
#include "Global.h"

PeaShooter::PeaShooter(Point position) {
	
	Sprite*sp = Sprite::create("peaShooter.png");
	setScale(0.3);
	sp->setScale(getScale());
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(1000);
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
	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	ScaleBy * scaleup = ScaleBy::create(0.5f, 1.25f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, NULL);
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

