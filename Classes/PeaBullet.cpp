#include "PeaBullet.h"

PeaBullet::PeaBullet(Point position):Bullet(Sprite::create("peaBullet.png"), position, 20, 6)
{

}

void PeaBullet::Hit_Animation()
{
}

void PeaBullet::Self_Animation()
{
}

void PeaBullet::move()
{
	double distance = 10;
	double time = distance / getSpeed();
	MoveTo *moveTo = MoveTo::create(time, ccp(500, getImg()->getPosition().y));
	Sequence *sequence = Sequence::create(DelayTime::create(0.1f), moveTo, NULL);
	getImg()->runAction(sequence);
}
