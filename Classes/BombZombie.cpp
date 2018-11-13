#include "BombZombie.h"
#include "Global.h"
#include <iostream>
using namespace map;
BombZombie::BombZombie(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	this->setEquip(nullptr);
	setWalkSpeed(10);
	setHp(25);
	setHead(true);
	setMeeting(false);
	setInterval(0.1);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Card\\BombZombie.png"));
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}
bool BombZombie::isWorking()
{
	int plant_cnt = 0;
	for (int i = 0; i < plantstatus.size(); i++)
	{
		int row = this->getRow();
		int col = Point2Rank(this->getImg()->getPosition()).second;
		if (plantstatus.at(i)->_row >= row - 1 && plantstatus.at(i)->_row <= row + 1 && plantstatus.at(i)->_col <= col + 1 && plantstatus.at(i)->_col >= col - 1)
		{
			plant_cnt += plantstatus.at(i)->plantVector.size();
		}

	}
	if (plant_cnt >= 3)
	{
		std::cout << "有" << plant_cnt << "个植物在附近，我要爆炸啦" << std::endl;
		return true;
	}
	return false;
}
void BombZombie::work()
{
	if (isWorking()&&!isOpening)
	{
		BoxOpen();
	}
}
void BombZombie::BoxOpen()
{
	Stop_Animation();
	if (!isOpening)
	{
		isOpening = true;
		//播放箱子打开动画
		Vector<SpriteFrame*> allframe;

		std::string prestr;

		prestr = "Zombies\\BombZombie\\Die\\";
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
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.22);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(BombZombie::Bomb, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		this->getImg()->runAction(sequence);
	}
	else
	{
		Bomb(this->getImg());
	}
}
void BombZombie::Bomb(Node* pSender)
{
	Sprite* bombSp= Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\BombZombie\\Boom\\1.png"));
	bombSp->setPosition(this->getImg()->getPosition());
	bombSp->setScale(2.1);
	Vector<SpriteFrame*> allframe;

	std::string prestr;

	prestr = "Zombies\\BombZombie\\Boom\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 6; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
		strcat(str, str1);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	auto fun = [this](Node*pSender)
	{
		pSender->removeFromParent();
	};
	auto actionDone = CallFuncN::create(fun);
	Sequence *sequence = Sequence::create(Animate::create(Animation::createWithSpriteFrames(allframe, 0.22)), actionDone, NULL);
	addLayer(bombSp);
	bombSp->runAction(sequence);
	Die(this->getImg());
	Bomb_damage();
}
void BombZombie::Bomb_damage()
{
	for (int i = 0; i < plantstatus.size(); i++)
	{
		int row = this->getRow();
		int col = Point2Rank(this->getImg()->getPosition()).second;
		if (plantstatus.at(i)->_row >= row - 1 && plantstatus.at(i)->_row <= row + 1 && plantstatus.at(i)->_col <= col + 1 && plantstatus.at(i)->_col >= col - 1)
		{
			for (int j = 0; j < plantstatus.at(i)->plantVector.size(); j++)
			{
				Plants* plant = plantstatus.at(i)->plantVector.at(j);
				if (strcmp(typeid(*plant).name(), "class Tomb") == 0)
				{
					continue;
				}
				plant->getHurt(30);
				plant->Attacked();
			}
		}
		
	}
}

void BombZombie::Die(Node * pSender)
{
	Sprite *sp = this->getImg();
	std::cout << "僵尸死了" << sp->getPositionX() << " " << sp->getPositionY() << std::endl;
	sp->getActionManager()->removeAllActionsFromTarget(sp);
	Sequence *sequence = Sequence::create(CallFuncN::create(CC_CALLBACK_1(BombZombie::clear_from_vector, this)), CallFuncN::create(CC_CALLBACK_1(BombZombie::clear, this)), NULL);
	sp->runAction(sequence);
}

void BombZombie::LostHead()
{
	if (!isOpening)
	{
		BoxOpen();
	}
}

void BombZombie::BasicMove()
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
	std::string prestr = "Zombies\\BombZombie\\Move\\";
	char str[100] = { 0 };
	char str1[100] = { 0 };
	for (int i = 1; i <= 8; i++)
	{
		strcpy(str, prestr.c_str());
		sprintf(str1, "%d.png", i);
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

void BombZombie::BasicAttack(PlantStatus * plantstatus)
{

	Vector<SpriteFrame*> allframe;
	std::string prestr = "Zombies\\BombZombie\\Attack\\";
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
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zombie::DamagePlant, this, plantstatus));
	Sequence* seq = CCSequence::create(Animate::create(an), actionDone, NULL);
	RepeatForever* rf = RepeatForever::create(seq);
	rf->setTag(Animation_Tag);
	this->getImg()->runAction(rf);
}
