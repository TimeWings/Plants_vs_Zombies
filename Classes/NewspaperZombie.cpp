#include "NewspaperZombie.h"
#include "Newspaper.h"
#include "Global.h"

NewspaperZombie::NewspaperZombie()
{
}

NewspaperZombie::NewspaperZombie(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);

	setWalkSpeed(7);
	setHp(12);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\NewspaperZombie\\NewspaperZombie.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	setEquip(new Newspaper());
	getEquip()->getImg()->setPosition(sp->getContentSize().width / 2, sp->getContentSize().height / 2);
	sp->addChild(getEquip()->getImg());
	this->setSche(sp);
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}

void NewspaperZombie::Attack(PlantStatus * plantstatus)
{
	if (!hasHead()) return;
	Stop_Animation();
	if (hasEquip())
	{
		Attack_with_Equip(plantstatus);
		getEquip()->Attack(getInterval());
	}
	else
	{
		BasicAttack(plantstatus);
	}
}

void NewspaperZombie::Attack_with_Equip(PlantStatus * plantstatus)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr;
	CCRepeatForever *rf;

	prestr = "Zombies\\NewspaperZombie\\Attackgif\\";

	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 4; i++)
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

	for (int i = 5; i <= 8; i++)
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

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, Animate::create(an1), NULL);
	rf = CCRepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void NewspaperZombie::BasicAttack(PlantStatus *plantstatus)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr;
	CCRepeatForever *rf;

	prestr = "Zombies\\NewspaperZombie\\Basic\\Attackgif\\";

	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 7; i++)
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

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(actionDone, Animate::create(an), NULL);
	rf = CCRepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void NewspaperZombie::Move()
{
	if (!hasHead()) return;
	Stop_Animation();
	if (hasEquip())
	{
		Move_with_Equip();
		getEquip()->Move();
	}
	else
	{
		BasicMove();
	}
}

void NewspaperZombie::Move_with_Equip()
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
	std::string prestr = "Zombies\\NewspaperZombie\\Walkgif\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 19; i++)
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

void NewspaperZombie::BasicMove()
{
	Sprite *sp = this->getImg();
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	std::cout << distance << " " << getPreWalkSpeed() << " " << time << std::endl;
	//std::cout << distance << " " << getPreWalkSpeed() << std::endl;
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);

	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Die, this));
	CCSequence *sequence = CCSequence::create(moveTo, scaledown, actionDone, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);

	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\NewspaperZombie\\Basic\\Walkgif\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 14; i++)
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

Sprite * NewspaperZombie::MagnetEquip()
{
	return nullptr;
}

void NewspaperZombie::Lost_Equip()
{
	if (hasEquip()) {
		getEquip()->getImg()->removeFromParent();
		setEquip(nullptr);
		setWalkSpeed(getPreWalkSpeed() * 2);
		setInterval(getInterval() / 2);
		if (hasHead()) {
			std::cout << "¼ÌÐø×ß" << std::endl;
			setMeeting(false);
			Move();
		}
	}
}
