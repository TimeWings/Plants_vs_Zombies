#include "BasicZombie.h"
#include "Global.h"
#include "iostream"

BasicZombie::BasicZombie()
{

}

BasicZombie::BasicZombie(Point position)
{
	setWalkSpeed(7);
	setHp(12);
	setHead(true);
	setInterval(1000);
	setBirthTime(0);
	Sprite *sp = Sprite::create("Zombies\\BasicZombie\\BasicZombie.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(1.5);
	sp->setPosition(position);
	this->Move();
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
	std::cout << "fuck" << std::endl;
	Sprite *sp = this->getImg();
	sp->getActionManager()->removeAllActionsFromTarget(sp);
	SpriteFrame *spf;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	for (int i = 1; i <= 21; i++)
	{
		sprintf(str, "Zombies\\BasicZombie\\Attackgif\\%02d.png", i);
		spf = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(spf);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.12);
	this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
}

void BasicZombie::Die()
{
	Sprite *sp = this->getImg();
	sp->getActionManager()->removeAllActionsFromTarget(sp);
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
	clear(sp);
}

void BasicZombie::Self_Animation()
{
	
}

void BasicZombie::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintby = CCTintBy::create(0.6, 0, 255, 255);
	sp->runAction(tintby);
}

void BasicZombie::LostHead()
{
	/*Sprite *sp = this->getImg();
	sp->getActionManager()->removeAllActionsFromTarget(sp);
	SpriteFrame *spf;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	for (int i = 1; i <= 22; i++)
	{
		sprintf(str, "Zombies\\BasicZombie\\Walkgif\\%02d.png", i);
		spf = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(spf);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.12);
	this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));*/
}

void BasicZombie::Move()
{
	Sprite *sp = this->getImg();
	sp->getActionManager()->removeAllActionsFromTarget(sp);
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getWalkSpeed();
	setActionManger(sp);
	MoveTo *moveTo = MoveTo::create(time, ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY()));
	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	CCSequence *sequence = CCSequence::create(moveTo, scaledown, NULL);
	sp->runAction(sequence);

	/*CCMotionStreak* streak = CCMotionStreak::create(0.8, 10, 10, ccRED, "circle.png");
	streak->runAction(moveTo);*/

	SpriteFrame *spf;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	for (int i = 1; i <= 22; i++)
	{
		sprintf(str, "Zombies\\BasicZombie\\Walkgif\\%02d.png", i);
		spf = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(spf);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.12);
	this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
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

