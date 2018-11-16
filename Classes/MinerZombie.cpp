#include "MinerZombie.h"
#include "Global.h"
#include "MinerCap.h"


MinerZombie::MinerZombie(Point position, int row, int col)
{
	this->isDigging = true;
	this->onGround = false;
	this->digSpeed = 12;

	this->setRow(row);
	this->setCol(col);
	setEquip(new MinerCap());
	setWalkSpeed(7);
	setHp(12);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\MinerZombie\\MinerZombie.png"));
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	this->Move();
	addLayer(sp);
}

void MinerZombie::Attack_with_Equip(PlantStatus * plantstatus)
{
	Vector<SpriteFrame*> allframe;
	std::string prestr;
	CCRepeatForever *rf;

	prestr = "Zombies\\MinerZombie\\Attack\\";

	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 10; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, this->getInterval());
	allframe.clear();

	//for (int i = 4; i <= 8; i++)
	//{
	//	strcpy(str, prestr.c_str());
	//	sprintf(str1, "%d.png", i);
	//	strcat(str, str1);
	//	auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
	//	auto frame = sprite->getSpriteFrame();
	//	allframe.pushBack(frame);
	//}
	//Animation* an1 = Animation::createWithSpriteFrames(allframe, this->getInterval());
	//allframe.clear();

	//for (int i = 9; i <= 10; i++)
	//{
	//	strcpy(str, prestr.c_str());
	//	sprintf(str1, "%d.png", i);
	//	strcat(str, str1);
	//	auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
	//	auto frame = sprite->getSpriteFrame();
	//	allframe.pushBack(frame);
	//}
	//Animation* an2 = Animation::createWithSpriteFrames(allframe, this->getInterval());
	//allframe.clear();

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, NULL);
	rf = CCRepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}

void MinerZombie::Move_with_Equip()
{
	Sprite *sp = this->getImg();
	if (isDigging)
	{
		sp->setPosition(ccp(sp->getPosition().x , (sp->getPosition().y - sp->getContentSize().height / 2)));
		float distance = sp->getPositionX() - map::Rank2Point(this->getRow(), 1).x + map::BlockSize.first / 2;
		double time;
		time = distance / digSpeed;
		Point a = Point (map::Rank2Point(this->getRow(), 1).x - map::BlockSize.first / 2,sp->getPositionY());
		MoveTo *moveTo = MoveTo::create(time, a);

		auto actionDone = CallFuncN::create(CC_CALLBACK_1(MinerZombie::OutMud, this));
		CCSequence *sequence = CCSequence::create(moveTo, actionDone, NULL);
		sequence->setTag(Animation_Tag);
		sp->runAction(sequence);

		Vector<SpriteFrame*> allframe;
		std::string prestr = "Zombies\\MinerZombie\\juedi\\";
		char str[100] = { 0 };
		char str1[100] = { 0 };
		for (int i = 1; i <= 12; i++)
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
	else if(onGround)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		float distance = sp->getContentSize().width * sp->getScaleX() / 2 + visibleSize.width - sp->getPositionX();
		double time;
		time = distance / getPreWalkSpeed();
		Point a = ccp(sp->getContentSize().width / 2 * sp->getScaleX() + visibleSize.width, sp->getPositionY());
		MoveTo *moveTo = MoveTo::create(time, a);

		auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Die, this));
		CCSequence *sequence = CCSequence::create(moveTo, actionDone, NULL);
		sequence->setTag(Animation_Tag);
		sp->runAction(sequence);


		Vector<SpriteFrame*> allframe;
		std::string prestr = "Zombies\\MinerZombie\\Move\\";
		char str[100] = { 0 };
		char str1[100] = { 0 };
		for (int i = 1; i <= 11; i++)
		{
			strcpy(str, prestr.c_str());
			sprintf(str1, "%d.png", i);
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
	
}

void MinerZombie::BasicMove()
{
	Sprite *sp = this->getImg();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float distance = sp->getContentSize().width * sp->getScaleX() / 2 + visibleSize.width - sp->getPositionX();
	double time = distance / getPreWalkSpeed();
	Point a = ccp(sp->getContentSize().width / 2 * sp->getScaleX() + visibleSize.width, sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BasicZombie::Die, this));
	CCSequence *sequence = CCSequence::create(moveTo, actionDone, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);

	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\MinerZombie\\Move_without_helmet\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 11; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
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

void MinerZombie::LostHead()
{
	this->setHead(false);
	if (hasEquip())
	{
		this->getEquip()->setHp(0);
	}
	Stop_Animation();
	Vector<SpriteFrame*> allframe;

	std::string prestr;

	prestr = "Zombies\\MinerZombie\\Die\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 12; i++)
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


void MinerZombie::OutMud(Node* pSender)
{
	this->getImg()->setPosition(ccp(this->getImg()->getPosition().x, (this->getImg()->getPosition().y + this->getImg()->getContentSize().height)));
	this->getImg()->stopAllActions();
	//僵尸出土
	onGround = true;
	//取消挖土
	isDigging = false;
	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\MinerZombie\\chutu\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 18; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.08);

	auto fun = [this](Node*psender)
	{
		this->Move();
		//出土之后才添加到数组里
		readyZombies.push_back(this);
	};
	auto call = CallFuncN::create(fun);

	CCSequence *sequence = CCSequence::create(Animate::create(an), call, NULL);
	this->getImg()->runAction(sequence);
}


