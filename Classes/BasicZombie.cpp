#include "BasicZombie.h"
#include "Global.h"
#include "iostream"
#include "EntityLayer.h"
#include "string"


BasicZombie::BasicZombie()
{

}

BasicZombie::BasicZombie(Point position,int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	this->setEquip(nullptr);
	setWalkSpeed(7);
	setHp(12);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\BasicZombie\\BasicZombie.png"));
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}

void BasicZombie::Attack(PlantStatus *plantstatus)
{
	Sprite *sp = this->getImg();
	if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
		sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
	BasicAttack(plantstatus);
}

void BasicZombie::BasicAttack(PlantStatus *plantstatus)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr;
	CCRepeatForever *rf;

	prestr = "Zombies\\BasicZombie\\Attackgif\\";

	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 6; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	for (int i = 7; i <= 11; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an1 = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	for (int i = 12; i <= 18; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an2 = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	for (int i = 19; i <= 21; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an3 = Animation::createWithSpriteFrames(allframe, this->getInterval());
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, Animate::create(an1), actionDone, Animate::create(an2), actionDone, Animate::create(an3), NULL);
	rf = CCRepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void BasicZombie::Die(Node * pSender)
{
	Sprite *sp = this->getImg();
	sp->getActionManager()->removeAllActionsFromTarget(sp);
	sp->removeAllChildrenWithCleanup(true);
	BasicDie(pSender);
}

void BasicZombie::BasicDie(Node *pSender)
{
	Sprite *sp = this->getImg();
	Vector<SpriteFrame*> allframe;
	std::string prestr;

	prestr = "Zombies\\BasicZombie\\Die\\";

	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 10; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	allframe.clear();


	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	Sequence *sequence = Sequence::create(CallFuncN::create(CC_CALLBACK_1(BasicZombie::clear_from_vector, this)), Animate::create(an), fadeout, CallFuncN::create(CC_CALLBACK_1(BasicZombie::clear, this)), NULL);
	sp->runAction(sequence);
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
	this->setHead(false);
	std::cout << "µôÍ·" << std::endl;
	Sprite *sp = this->getImg();
	if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
		sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
	Vector<SpriteFrame*> allframe;

	std::string prestr;

	CCRepeatForever *rf;
	Animation* an;
	if (this->isMeeting()) {
		prestr = "Zombies\\BasicZombie\\Attackgif_without_head\\";
		char str[100] = { 0 };
		char str1[100] = { 0 };
		for (int i = 1; i <= 5; i++)
		{
			strcpy(str, prestr.c_str());
			sprintf(str1, "%02d.png", i);
			strcat(str, str1);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		an = Animation::createWithSpriteFrames(allframe, this->getInterval());
		allframe.clear();
		
	}
	else {
		if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
		{
			sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
		}
		float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
		double time = distance / getPreWalkSpeed();
		std::cout << distance << " " << getPreWalkSpeed() << std::endl;
		Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
		MoveTo *moveTo = MoveTo::create(time, a);

		ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
		CCSequence *sequence = CCSequence::create(moveTo, scaledown, NULL);
		//sequence->setTag(Animation_Tag);
		sp->runAction(sequence);
		prestr = "Zombies\\BasicZombie\\Walkgif_without_head\\";
		char str[100] = { 0 };
		char str1[100] = { 0 };
		for (int i = 1; i <= 5; i++)
		{
			strcpy(str, prestr.c_str());
			sprintf(str1, "%02d.png", i);
			strcat(str, str1);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		an = Animation::createWithSpriteFrames(allframe, 0.2);
		allframe.clear();
	}
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Die, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	this->getImg()->runAction(sequence);
	
	prestr = "Zombies\\BasicZombie\\LostHead\\";
	Sprite *lh = Sprite::createWithTexture(TextureCache::getInstance()->addImage("none.png"));
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 12; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	lh->setScale(sp->getScale());
	auto actionDonehead = CallFuncN::create(CC_CALLBACK_1(BasicZombie::clear, this));
	Sequence *sequencehead = Sequence::create(Animate::create(Animation::createWithSpriteFrames(allframe, 0.2)), actionDonehead, NULL);
	lh->runAction(sequencehead);
	allframe.clear();
	lh->setPosition(sp->getPosition());
	addLayer(lh);
}

void BasicZombie::Move()
{
	Sprite *sp = this->getImg();
	if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
	{
		sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
	}
	BasicMove();
}

void BasicZombie::BasicMove()
{
	Sprite *sp = this->getImg();
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	std::cout << distance << " " << getPreWalkSpeed() << std::endl;
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);

	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Die, this));
	CCSequence *sequence = CCSequence::create(moveTo, scaledown, actionDone, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);

	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\BasicZombie\\Walkgif\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 22; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.12);
	CCRepeatForever *rf = CCRepeatForever::create(Animate::create(an));
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void BasicZombie::DamageZombie(int damage)
{
	setHp(getHp() - damage);
	Attacked();
}

void BasicZombie::DamageEquip(int damage)
{
	DamageZombie(damage);
}

void BasicZombie::DamageBoth(int damage)
{
	DamageZombie(damage);
}

Sprite * BasicZombie::MagnetEquip()
{
	return nullptr;
}



