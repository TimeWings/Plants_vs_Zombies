#include "Gargantuar.h"
#include "Global.h"

Gargantuar::Gargantuar()
{
}

Gargantuar::Gargantuar(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	this->setEquip(nullptr);
	setWalkSpeed(5);
	setHp(3000);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\Gargantuar\\Gargantuar.png"));
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(Point(position.x, position.y + getImg()->getContentSize().height * 0.3));
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}

void Gargantuar::Attack(PlantStatus * plantstatus)
{
	if (!hasHead()) return;
	Stop_Animation();
	BasicAttack(plantstatus);
}

void Gargantuar::BasicAttack(PlantStatus * plantstatus)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr;
	CCRepeatForever *rf;

	prestr = "Zombies\\Gargantuar\\Attackgif\\";

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
	Animation* an = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	for (int i = 13; i <= 19; i++)
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

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Gargantuar::DamagePlant, this, plantstatus));
	auto actionDone2 = CallFuncN::create(CC_CALLBACK_1(Gargantuar::AfterAttack, this));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, Animate::create(an1), actionDone2, NULL);
	rf = CCRepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void Gargantuar::AfterAttack(Node * pSender)
{
	this->setMeeting(false);
	this->Move();
}

void Gargantuar::Move()
{
	if (!hasHead()) return;
	Stop_Animation();
	BasicMove();
}

void Gargantuar::BasicMove()
{
	Sprite *sp = this->getImg();
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	std::cout << distance << " " << getPreWalkSpeed() << std::endl;
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);

	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Gargantuar::Die, this));
	CCSequence *sequence = CCSequence::create(moveTo, scaledown, actionDone, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);

	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\Gargantuar\\Walkgif\\";
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
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.35);
	CCRepeatForever *rf = CCRepeatForever::create(Animate::create(an));
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void Gargantuar::DamagePlant(Node * pSender, PlantStatus * plantstatus)
{
	for (int i = 0; i < plantstatus->plantVector.size(); i++)
	{
		Press(plantstatus->plantVector.at(i));
		plantstatus->plantVector.erase(plantstatus->plantVector.begin() + i);
		i--;
	}
}

void Gargantuar::Press(Plants * plant)
{
	std::cout << "Ñ¹ËÀ£¡£¡£¡" << std::endl;
	plant->getImg()->getActionManager()->removeAllActionsFromTarget(plant->getImg());
	float preScale = plant->getImg()->getScaleX();
	//Ñ¹±â
	CCScaleBy * scaleupx_ZB = CCScaleBy::create(0.2f, 0.8, 0.2);
	//½©Ê¬Î»ÖÃÉÔÎ¢ÏÂ×¹
	MoveTo *moveTo = MoveTo::create(0.5, ccp(plant->getImg()->getPositionX(), plant->getImg()->getPositionY() - 10));
	//ºÏ³É¶ÓÁÐ
	CCFiniteTimeAction * spawn = CCSpawn::create(scaleupx_ZB, moveTo, NULL);
	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(Gargantuar::clearPlant, this, plant));
	Sequence *sequence = Sequence::create(spawn, actionDone1, NULL);
	plant->getImg()->runAction(sequence);
}

void Gargantuar::clearPlant(Node* pSender, Plants* plant)
{
	plant->Die();
}

void Gargantuar::LostHead()
{
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Gargantuar::Die, this));
	this->getImg()->runAction(actionDone);
}

void Gargantuar::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

void Gargantuar::Die(Node * pSender)
{
	Sprite *sp = this->getImg();
	sp->getActionManager()->removeAllActionsFromTarget(sp);
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	Sequence *sequence = Sequence::create(CallFuncN::create(CC_CALLBACK_1(Gargantuar::clear_from_vector, this)), fadeout, CallFuncN::create(CC_CALLBACK_1(Gargantuar::clear, this)), NULL);
	sp->runAction(sequence);
}

void Gargantuar::DamageZombie(int damage)
{
	setHp(getHp() - damage);
	Attacked();
}

void Gargantuar::DamageEquip(int damage)
{
	DamageZombie(damage);
}

void Gargantuar::DamageBoth(int damage)
{
	DamageZombie(damage);
}

Sprite * Gargantuar::MagnetEquip()
{
	return nullptr;
}

