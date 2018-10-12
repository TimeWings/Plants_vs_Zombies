#include "PeaBullet.h"
#include "Global.h"
#include <iostream>

PeaBullet::PeaBullet(Point position):Bullet(position, 20, 6)
{
	srand((unsigned)time(NULL));
	int cnt = rand() % 4+1;
	Sprite *sp;
	if(cnt==1)
		sp = Sprite::create("sword1.png");
	else if(cnt==2)
		sp = Sprite::create("sword2.png");
	else if(cnt==3)
		sp = Sprite::create("sword3.png");
	else
		sp = Sprite::create("sword4.png");
	sp->setScale(0.2);
	setScale(0.3);
	sp->setPosition(position);
	preBullet.insert(this, sp);
}

void PeaBullet::work(Sprite * sp)
{
	Self_Animation(sp);
}

void PeaBullet::Hit_Animation(Sprite*sp)
{
	readyBullet.erase(this);
	ActionInterval * fadeout = FadeOut::create(0.3);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clear, this, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
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
	//MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width-50, sp->getPosition().y));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clear, this,this));
	Sequence *sequence = Sequence::create(moveTo, actionDone, NULL);
	sp->runAction(sequence);
}

void PeaBullet::clear(Node *pSender,Bullet* bullet) 
{
	//std::cout << "ÉÁÉÁµÄ½£±»Çå³ý" << std:: endl;
	pSender->removeFromParent();
	readyBullet.erase(bullet);
}


