#include "PeaShooter.h"
#include "PeaBullet.h"
#include "Global.h"
PeaShooter::PeaShooter(Point position) 
{
	Sprite*sp = Sprite::create("peaShooter.png");
	this->setImg(sp);
	this->getImg()->setPosition(position);
	this->setHp(20);
	this->setInterval(0.5);
}

void PeaShooter::Attack()
{

}

void PeaShooter::Die()
{
}

void PeaShooter::Self_Animation()
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
	getImg()->runAction(RepeatForever::create(Animate::create(an)));
}

void PeaShooter::Attack_Animation()
{
}

void PeaShooter::Attacked()
{
}

bool PeaShooter::isAttacking()
{
	return false;
}

void PeaShooter::CreateBullet()
{
	Bullet *pb = new PeaBullet(Point(getImg()->getPositionX()+getImg()->getContentSize().width / 2, getImg()->getContentSize().height / 2 + getImg()->getPositionY() / 2));
	preBullet.push_back(pb);
}

