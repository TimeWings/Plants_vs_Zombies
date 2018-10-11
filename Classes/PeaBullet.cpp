#include "PeaBullet.h"
#include "Global.h"

PeaBullet::PeaBullet(Point position):Bullet(position, 20, 6)
{
	Sprite* sp = Sprite::create("peaBullet.png");
	sp->setPosition(position);
	preBullet.insert(this, sp);
}

void PeaBullet::Hit_Animation(Sprite*sp)
{
}

void PeaBullet::Self_Animation(Sprite*sp)
{
}

void PeaBullet::move(Sprite*sp)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double distance = 10;
	double time = distance / getSpeed();
	MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width+sp->getContentSize().width, sp->getPosition().y));
	Sequence *sequence = Sequence::create(DelayTime::create(0.1f), moveTo, NULL);
	sp->runAction(sequence);
}
