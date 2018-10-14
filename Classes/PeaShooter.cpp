#include "PeaShooter.h"
#include "PeaBullet.h"
#include "Global.h"
#include <iostream>

PeaShooter::PeaShooter(Point position) {
	
	Sprite*sp = Sprite::create("peaShooter.png");
	this->setImg(sp);
	sp->retain();
	setScale(0.3);
	sp->setScale(getScale());
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	prePlants.push_back(this);

}
PeaShooter::PeaShooter() 
{
}
void PeaShooter::work()
{
	CreateBullet();
}

void PeaShooter::Die()
{
	Sprite*sp = this->getImg();
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaShooter::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void PeaShooter::Self_Animation()
{
	Sprite *sp = this->getImg();
	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	ScaleBy * scaleup = ScaleBy::create(0.5f, 1.25f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, NULL);
	sp->runAction(RepeatForever::create(sequence));
	
}

void PeaShooter::init()
{
	Self_Animation();
}


void PeaShooter::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintby = CCTintBy::create(0.6, 0, 255, 255);
	sp->runAction(tintby);
}

bool PeaShooter::isAttacking()
{
	return false;
}

void PeaShooter::CreateBullet()
{
	Sprite *sp = this->getImg();
	//std::cout<<sp << "ÉÁÉÁµÄ½£Éú³É" << std::endl;
	Point a = ccp(sp->getPositionX() + sp->getContentSize().width*sp->getScale()/2, sp->getContentSize().height*sp->getScale()/ 4 + sp->getPositionY());
	Bullet *pb = new PeaBullet(a);
}

void PeaShooter::clear(Node *pSender)
{
	//std::cout << "ÉÁÉÁËÀÍö" << std::endl;
	pSender->removeFromParent();
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
}

