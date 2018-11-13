#include "FootBallZombie.h"
#include "Global.h"
FootBallZombie::FootBallZombie(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	setEquip(new SafetyHelmet());
	setWalkSpeed(15);
	setHp(42);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Card\\FootBallZombie.png"));
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}

void FootBallZombie::BasicAttack(PlantStatus * plantstatus)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\FootballZombie\\Attack_without_helmet\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 11; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.05);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, NULL);
	RepeatForever* rf = RepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void FootBallZombie::Attack_with_Equip(PlantStatus * plantstatus)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\FootballZombie\\Attack\\";
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
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.05);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, NULL);
	RepeatForever* rf = RepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}
void FootBallZombie::Lost_Equip()
{
	if (hasEquip()) {
		getEquip()->getImg()->removeFromParent();
		setEquip(nullptr);
		if (hasHead()) {
			Lost_Equip_Animation();
			setMeeting(false);
			Move();
		}
	}
}
void FootBallZombie::Lost_Equip_Animation()
{
	auto none = Sprite::createWithTexture(TextureCache::getInstance()->addImage("none.png"));
	none->setPosition(this->getImg()->getPositionX(), this->getImg()->getPositionY() + this->getImg()->boundingBox().size.height / 2);
	none->setScale(1.8);
	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\FootballZombie\\Lost_helmet\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 3; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.3);
	auto fun = [this](Node*pSender)
	{
		pSender->removeFromParent();
	};
	auto actionDone = CallFuncN::create(fun);
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	addLayer(none);
	none->runAction(sequence);
}
void FootBallZombie::Move_with_Equip()
{
	Sprite *sp = this->getImg();
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	//std::cout << distance << " " << getPreWalkSpeed() << std::endl;
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Die, this));
	CCSequence *sequence = CCSequence::create(moveTo, actionDone, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);

	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\FootballZombie\\Move\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 11; i++)
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

void FootBallZombie::BasicMove()
{
	Sprite *sp = this->getImg();
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	//std::cout << distance << " " << getPreWalkSpeed() << std::endl;
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Die, this));
	CCSequence *sequence = CCSequence::create(moveTo, actionDone, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);

	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\FootballZombie\\Move_without_helmet\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 11; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%02d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.12);
	RepeatForever *rf = RepeatForever::create(Animate::create(an));
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void FootBallZombie::LostHead()
{
	this->setHead(false);
	if (hasEquip())
		this->getEquip()->setHp(0);
	Sprite *sp = this->getImg();
	if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
		sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
	Vector<SpriteFrame*> allframe;

	std::string prestr;
	prestr = "Zombies\\FootballZombie\\Die\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 7; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.3);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(FootBallZombie::Die, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	this->getImg()->runAction(sequence);
	
}
Sprite * FootBallZombie::MagnetEquip()
{
	if (!hasEquip())
		return nullptr;
	getEquip()->Die();
	setEquip(nullptr);
	if (hasHead()) {
		setMeeting(false);
		Move();
	}
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\FootballZombie\\Lost_helmet\\1.png"));
	sp->setScale(1.5);
	sp->setPosition(this->getImg()->getPosition().x, this->getImg()->getPosition().y+this->getImg()->getBoundingBox().size.height/2);
	addLayer(sp);
	return sp;
}
