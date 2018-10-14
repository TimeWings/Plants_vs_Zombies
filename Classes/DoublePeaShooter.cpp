#include "DoublePeaShooter.h"
#include "PeaBullet.h"
#include "Global.h"
#include "DoubleBullet.h"
DoublePeaShooter::DoublePeaShooter(Point position):PeaShooter()
{
	Sprite*sp = Sprite::create("doubleShooter.png");
	this->setImg(sp);
	sp->retain();
	setScale(0.2);
	sp->setScale(getScale());
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	prePlants.push_back(this);
}

void DoublePeaShooter::CreateBullet()
{
	Sprite *sp = this->getImg();
	Point a = ccp(sp->getPositionX() + sp->getContentSize().width*sp->getScale() / 2, sp->getContentSize().height*sp->getScale() / 4 + sp->getPositionY());
	Bullet *pb = new DoubleBullet(a);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(DoublePeaShooter::addBullet, this,sp));
	CCFiniteTimeAction * reveseseq = CCSequence::create(CCDelayTime::create(0.2) , actionDone, NULL);
	sp->runAction(reveseseq);
}

void DoublePeaShooter::addBullet(Node * pSender, Sprite * sp)
{
	Point a = ccp(sp->getPositionX() + sp->getContentSize().width*sp->getScale() / 2, sp->getContentSize().height*sp->getScale() / 4 + sp->getPositionY());
	Bullet *pb = new DoubleBullet(a);
}
