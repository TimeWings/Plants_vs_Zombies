#include "PeaShooter.h"
#include "PeaBullet.h"
#include "Global.h"

PeaShooter::PeaShooter(Point position) {
	
	Sprite*sp = Sprite::create("peaShooter.png");
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(0.5);
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
	Vector<SpriteFrame*> allframe;
	for (int i = 0; i < 2; i++)
	{
		if (i == 0) {
			SpriteFrame *sp = SpriteFrame::create("peaShooter.png", Rect(0, 0, 512, 724));
			allframe.pushBack(sp);
		}
		else {
			SpriteFrame *sp = SpriteFrame::create("peaShooter.png", Rect(0, 0, 512, 724));
			allframe.pushBack(sp);
		}

	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.5);
	sp->runAction(RepeatForever::create(Animate::create(an)));
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

