#include "PeaBullet.h"
#include "Global.h"
#include <iostream>

PeaBullet::PeaBullet()
{
	this->setDamage(20);
	this->setSpeed(6);
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
	sp->setScale(0.15);
	this->setImg(sp);
	sp->retain();
	//std::cout << sp->getContentSize().width << std::endl;
	sp->setPosition(position.x+sp->getContentSize().width*sp->getScale()/2,position.y);
	preBullet.push_back(this);
}

void PeaBullet::work()
{
	Self_Animation();
}

void PeaBullet::Hit_Animation(Sprite * sp1, std::vector<int>debuff, Vector<Action*>action)
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
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

Sprite* PeaBullet::attack_Animation()
{
	Sprite*sp = this->getImg();
	Sprite * hole = Sprite::create("circle.png");
	hole->setPosition(Vec2(sp->getPositionX() - sp->getContentSize().width*(sp->getScale() - 0.1), sp->getPositionY()));
	//std::cout << "光环：" << hole->getPositionX() << "  " << hole->getPositionY() << std::endl;
	ActionInterval * fadeout = FadeOut::create(0.7);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clear1, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	hole->runAction(sequence);
	return hole;
}
void PeaBullet::Self_Animation()
{
}

void PeaBullet::move()
{
	Sprite*sp = this->getImg();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double distance = (visibleSize.width+sp->getContentSize().width*sp->getScale() -sp->getPositionX())/15;
	double time = distance / getSpeed();
	MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width+sp->getContentSize().width*sp->getScale(), sp->getPosition().y));
	//MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width-50, sp->getPosition().y));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clear, this));
	Sequence *sequence = Sequence::create(moveTo, actionDone, NULL);
	sp->runAction(sequence);
}

void PeaBullet::clear(Node *pSender) 
{
	//std::cout << "闪闪的剑被清除" << std:: endl;
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
void PeaBullet::clear1(Node *pSender)
{
	//std::cout << "双刀被清除" << std:: endl;
	pSender->removeFromParent();
}


