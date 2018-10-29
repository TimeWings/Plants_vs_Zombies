#include "BasicZombie.h"
#include "Global.h"
#include "iostream"

BasicZombie::BasicZombie()
{

}

BasicZombie::BasicZombie(Point position,int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	setWalkSpeed(7);
	setHp(12);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite *sp = Sprite::create("Zombies\\BasicZombie\\BasicZombie.png");
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
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

void BasicZombie::attack(Plants *plant)
{
	std::cout << "½©Ê¬¹¥»÷" << std::endl;
	Sprite *sp = this->getImg();
	if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
		sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
	SpriteFrame *spf;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	for (int i = 1; i <= 6; i++)
	{
		sprintf(str, "Zombies\\BasicZombie\\Attackgif\\%02d.png", i);
		spf = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(spf);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	for (int i = 7; i <= 11; i++)
	{
		sprintf(str, "Zombies\\BasicZombie\\Attackgif\\%02d.png", i);
		spf = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(spf);
	}
	Animation* an1 = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	for (int i = 12; i <= 18; i++)
	{
		sprintf(str, "Zombies\\BasicZombie\\Attackgif\\%02d.png", i);
		spf = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(spf);
	}
	Animation* an2 = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	for (int i = 19; i <= 21; i++)
	{
		sprintf(str, "Zombies\\BasicZombie\\Attackgif\\%02d.png", i);
		spf = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(spf);
	}
	Animation* an3 = Animation::createWithSpriteFrames(allframe, this->getInterval());
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Damage, this, plant));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, Animate::create(an1), actionDone, Animate::create(an2), actionDone, Animate::create(an3), NULL);
	CCRepeatForever *rf = CCRepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
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

void BasicZombie::Damage(Node * pSender, Plants * plant)
{
	plant->getHurt(1);
	plant->Attacked();
}

void BasicZombie::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
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
	if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
	{
		sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
	}
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	std::cout << distance <<" "<< getPreWalkSpeed() << std::endl;
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);

	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	CCSequence *sequence = CCSequence::create(moveTo, scaledown, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);


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
	CCRepeatForever *rf = CCRepeatForever::create(Animate::create(an));
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
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

