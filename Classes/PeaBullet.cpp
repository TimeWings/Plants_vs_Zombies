#include "PeaBullet.h"
#include "Global.h"
#include "Bullet.h"
#include "Entity.h"
#include <iostream>

PeaBullet::PeaBullet()
{
}
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
	this->setImg(sp);
	sp->retain();
	//std::cout << sp->getContentSize().width << std::endl;
	sp->setPosition(position.x+sp->getContentSize().width*sp->getScaleX()/2,position.y);
	this->addLayer(sp);
	this->attack_Animation();
	readyBullet.push_back(this);
	this->move();
}

void PeaBullet::Hit_Animation(TestZombie* zombie)
{
	Sprite* sp = this->getImg();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
	ActionInterval * fadeout = FadeOut::create(0.3);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clearNode, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}


void PeaBullet::attack_Animation()
{
	Sprite*sp = this->getImg();
	Sprite * hole = Sprite::create("circle.png");
	hole->setPosition(Vec2(sp->getPositionX() - sp->getContentSize().width*(sp->getScaleX() ), sp->getPositionY()));
	//std::cout << "¹â»·£º" << hole->getPositionX() << "  " << hole->getPositionY() << std::endl;
	ActionInterval * fadeout = FadeOut::create(0.7);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clearNode, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	this->addLayer(hole);
	hole->runAction(sequence);
}

void PeaBullet::move()
{
	Sprite*sp = this->getImg();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double distance = (visibleSize.width+sp->getContentSize().width*sp->getScaleX() -sp->getPositionX())/15;
	double time = distance / getSpeed();
	MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width+sp->getContentSize().width*sp->getScaleX(), sp->getPosition().y));
	//MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width-50, sp->getPosition().y));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clear, this));
	Sequence *sequence = Sequence::create(moveTo, actionDone, NULL);
	sp->runAction(sequence);
}

void PeaBullet::clear(Node * pSender)
{
	pSender->removeFromParent();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
}

void PeaBullet::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}



