#include "PeaShooter.h"
#include "PeaBullet.h"
#include "Global.h"
#include <iostream>

PeaShooter::PeaShooter(Point position) {
	
	Sprite*sp = Sprite::create("peaShooter.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	this->Self_Animation();
	addLayer(sp);
	readyPlants.push_back(this);

}
PeaShooter::PeaShooter() 
{
}
bool PeaShooter::isWorking()
{
	return true;
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
void PeaShooter::Self_Animation()
{
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(0.7f, preScale, preScale + 0.05);
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale, preScale);
	Sequence *sequence1 = Sequence::create(scaleup, scaledown, NULL);
	CCActionInterval * moveBy = CCMoveBy::create(1, ccp(7, 0));
	CCActionInterval * actionmoveback = moveBy->reverse();
	CCFiniteTimeAction * spawn1 = CCSpawn::create(sequence1, moveBy, NULL);
	CCFiniteTimeAction * spawn2 = CCSpawn::create(sequence1, actionmoveback, NULL);
	Sequence *sequence2 = Sequence::create(spawn1, spawn2, NULL);
	sp->runAction(CCRepeatForever::create(sequence2));
}
void PeaShooter::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite *sp = this->getImg();
	//std::cout<<sp << "ÉÁÉÁµÄ½£Éú³É" << std::endl;
	Point a = ccp(sp->getPositionX() , sp->getContentSize().height*sp->getScaleY()/ 4 + sp->getPositionY());
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

