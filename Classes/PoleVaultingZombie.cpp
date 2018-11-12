#include "PoleVaultingZombie.h"
#include "Global.h"
using namespace map;
PoleVaultingZombie::PoleVaultingZombie(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	this->setEquip(nullptr);
	setWalkSpeed(14);
	setHp(14);
	setHead(true);
	setMeeting(false);
	setInterval(0);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\PoleVaultingZombie\\PoleVaultingZombie.png"));
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}
//跳完还要减速
void PoleVaultingZombie::Jump(bool canMove)
{
	Stop_Animation();
	this->getDebuff()->push_back(Jumping_Tag);
	hasPole = false;
	Sprite *sp = this->getImg();
	MoveTo *moveTo;
	double time;
	if (canMove)
	{
		float distance = BlockSize.first*0.8;
		time = distance / getPreWalkSpeed() / 1.8;
		Point a = ccp(this->getImg()->getPositionX() - distance, sp->getPositionY());
		moveTo = MoveTo::create(time / 16 * 12, a);
	}
	else
	{
		float distance = -10;
		time = BlockSize.first*0.8 / getPreWalkSpeed() / 1.8;
		Point a = ccp(this->getImg()->getPositionX() - distance, sp->getPositionY());
		moveTo = MoveTo::create(time / 16 * 12, a);
	}
	ActionInterval * easeSineIn = EaseSineIn::create(moveTo);
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	for (int i = 1; i <= 16; i++)
	{
		sprintf(str, "Zombies\\PoleVaultingZombie\\Jump\\%02d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, time/16);
	Spawn* spawn = Spawn::create(Animate::create(an), easeSineIn, NULL);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PoleVaultingZombie::afterJump, this));
	Sequence *sequence = Sequence::create(spawn, actionDone, NULL);
	this->getImg()->runAction(sequence);
}
void PoleVaultingZombie::afterJump(Node * pSender)
{
	setWalkSpeed(getPreWalkSpeed() / 1.5);
	for (int i=0;i<getDebuff()->size();i++)
	{
		if (getDebuff()->at(i) == Jumping_Tag)
		{
			getDebuff()->erase(getDebuff()->begin() + i);
			break;
		}
	}
	this->Move();
}

void PoleVaultingZombie::LostHead()
{
	this->setHead(false);
	if (hasEquip())
		this->getEquip()->setHp(0);
	Sprite *sp = this->getImg();
	if (sp->getActionManager()->getActionByTag(Animation_Tag, sp) != NULL)
		sp->getActionManager()->removeAllActionsByTag(Animation_Tag, sp);
	Vector<SpriteFrame*> allframe;

	std::string prestr;
	if (this->isMeeting())
	{
		prestr = "Zombies\\PoleVaultingZombie\\Attackgif_without_head\\";
		char str[100] = { 0 };
		char str1[100] = { 0 };
		for (int i = 1; i <= 23; i++)
		{
			strcpy(str, prestr.c_str());
			sprintf(str1, "%02d.png", i);
			strcat(str, str1);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe,0.1);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(PoleVaultingZombie::Die, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		this->getImg()->runAction(sequence);
	}
	else 
	{

		prestr = "Zombies\\PoleVaultingZombie\\Walkgif_without_head\\";
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
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.4);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(PoleVaultingZombie::Die, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		this->getImg()->runAction(sequence);
	}
	

}

void PoleVaultingZombie::BasicMove()
{
	Sprite *sp = this->getImg();
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PoleVaultingZombie::Die, this));
	CCSequence *sequence = CCSequence::create(moveTo, actionDone, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);

	Vector<SpriteFrame*> allframe;
	if (hasPole)
	{
		std::string prestr = "Zombies\\PoleVaultingZombie\\Walkgif_with_pole\\";
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
	}
	else
	{
		std::string prestr = "Zombies\\PoleVaultingZombie\\Walkgif\\";
		char str[100] = { 0 };
		char str1[100] = { 0 };
		for (int i = 1; i <= 25; i++)
		{
			strcpy(str, prestr.c_str());
			sprintf(str1, "%02d.png", i);
			strcat(str, str1);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.12);
	CCRepeatForever *rf = CCRepeatForever::create(Animate::create(an));
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void PoleVaultingZombie::BasicAttack(PlantStatus * plantstatus)
{
	if (hasPole)
	{
		bool flag = true;
		for (auto x : plantstatus->plantVector)
		{
			if (strcmp(typeid(*x).name(), "class NutPlus") == 0)
			{
				flag = false;
				break;
			}
		}
		Jump(flag);
		return;
	}
	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\PoleVaultingZombie\\Attackgif\\";
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
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.05);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, NULL);
	RepeatForever* rf = RepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}
