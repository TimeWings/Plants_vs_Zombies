#include "PeaShooter.h"
#include "PeaBullet.h"
#include "Global.h"
#include <iostream>

PeaShooter::PeaShooter(Point position) {
	
	Sprite*sp = Sprite::create("peaShooter.png");
	setScale(0.3);
	sp->setScale(getScale());
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(1000);
	prePlants.insert(this, sp);

}
void PeaShooter::work(Sprite* sp)
{
	CreateBullet(sp);
}

void PeaShooter::Die(Sprite *sp)
{
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaShooter::clear, this,this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void PeaShooter::Self_Animation(Sprite *sp)
{
	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	ScaleBy * scaleup = ScaleBy::create(0.5f, 1.25f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, NULL);
	sp->runAction(RepeatForever::create(sequence));

}

void PeaShooter::init(Sprite * sp)
{
	Self_Animation(sp);
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
	std::cout << "ÉÁÉÁµÄ½£Éú³É" << std::endl;
	Point a = Point(sp->getPositionX() + sp->getContentSize().width/2, sp->getContentSize().height*sp->getScale()/ 4 + sp->getPositionY());
	Bullet *pb = new PeaBullet(a);
}

void PeaShooter::clear(Node *pSender, Plants* plant)
{
	std::cout << "ÉÁÉÁËÀÍö" << std::endl;
	pSender->removeFromParent();
	readyPlants.erase(plant);
}

