#include "DuckZombie.h"
#include "Global.h"

DuckZombie::DuckZombie(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	this->setEquip(nullptr);
	setWalkSpeed(7);
	setHp(12);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\DuckZombie\\DuckZombie.png"));
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}

void DuckZombie::BasicAttack(PlantStatus * plantstatus)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr;
	CCRepeatForever *rf;

	prestr = "Zombies\\DuckZombie\\Attack\\";

	char str[100] = { 0 };
	char str1[100] = { 0 };

	for (int i = 1; i <= 9; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, this->getInterval());
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, NULL);
	rf = CCRepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void DuckZombie::BasicMove()
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
	std::string prestr = "Zombies\\DuckZombie\\WalkInWater\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 30; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	CCRepeatForever *rf = CCRepeatForever::create(Animate::create(an));
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);	
}

void DuckZombie::LostHead()
{
	this->setHead(false);
	if (hasEquip())
		this->getEquip()->setHp(0);
	Stop_Animation();
	Vector<SpriteFrame*> allframe;

	std::string prestr;

	prestr = "Zombies\\DuckZombie\\Die\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 19; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Die, this));
	Sequence *sequence = Sequence::create(Animate::create(Animation::createWithSpriteFrames(allframe, 0.12)), actionDone, NULL);
	this->getImg()->runAction(sequence);
}
