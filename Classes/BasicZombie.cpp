#include "BasicZombie.h"
#include "Global.h"

BasicZombie::BasicZombie()
{

}

BasicZombie::BasicZombie(Point position)
{
	setWalkSpeed(5);
	setHp(12);
	setHand(true);
	setHead(true);
	setInterval(1000);
	setBirthTime(0);
	Sprite *sp = Sprite::create("sunFlower.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->Self_Animation();
	addLayer(sp);
	readyZombies.push_back(this);
}

bool BasicZombie::isAttacking()
{
	return false;
}

void BasicZombie::attack()
{
}

void BasicZombie::Die()
{
	Sprite*sp = this->getImg();
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
	clear(sp);
}

void BasicZombie::Self_Animation()
{
	float distance = 100;
	double time = distance / getWalkSpeed();
	Sprite *sp = this->getImg();
	setActionManger(sp);
	MoveTo *moveTo = MoveTo::create(time, ccp(0, sp->getPositionY()));
	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	CCSequence *sequence = CCSequence::create(moveTo, scaledown, NULL);
	sp->runAction(sequence);
	
	/*CCMotionStreak* streak = CCMotionStreak::create(0.8, 10, 10, ccRED, "circle.png");
	streak->runAction(moveTo);*/
}

void BasicZombie::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintby = CCTintBy::create(0.6, 0, 255, 255);
	sp->runAction(tintby);
}

void BasicZombie::LostHand()
{
}

void BasicZombie::LostHead()
{
}

void BasicZombie::clear(Node * pSender)
{
	pSender->removeFromParent();
	for (unsigned i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i) == this)
		{
			readyZombies.erase(readyZombies.begin() + i);
			break;
		}
	}
}

