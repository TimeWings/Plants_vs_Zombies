#include "WhiteJannu.h"
#include "Global.h"

WhiteJannu::WhiteJannu(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("JannuDarkruku\\WhiteJannu.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.25);
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(5000);
	Self_Animation();
	//添加到植物层（显示）
	addLayer(sp);
	readyPlants.push_back(this);
}

bool WhiteJannu::isWorking()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (readyZombies.size() > 0)
	{
		for (auto x : readyZombies)
		{
			if (x->getImg()->getPositionX() < visibleSize.width)
			{
				return true;
			}
		}
	}
	return false;
}


void WhiteJannu::work()
{
	if (isWorking())
	{
		Effect(this->getImg());
	}
}

void WhiteJannu::Effect(Node * pSender)
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	creatSprite();
	setNewBirthTime();
}

void WhiteJannu::creatSprite()
{
	//遍历植物加上血和无敌buff
	for (auto x : readyPlants)
	{
		//加血
		auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("JannuDarkruku\\recover\\1.png"));
		Vector<SpriteFrame*> allframe;
		char str[100] = { 0 };
		for (int i = 1; i <= 21; i++)
		{
			sprintf(str, "JannuDarkruku\\recover\\%d.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
		sp->setPosition(x->getImg()->getPosition());
		sp->setScale(1.5);
		addLayer(sp);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaShooter::clear, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		sp->runAction(sequence);
		//加血5点
		x->setHp(x->getHp() + 5);
		//护盾
		auto sp1 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("JannuDarkruku\\defense\\1.png"));
		Vector<SpriteFrame*> allframe1;
		for (int i = 1; i <= 17; i++)
		{
			sprintf(str, "JannuDarkruku\\defense\\%d.png", i);
			auto sprite1 = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame1 = sprite1->getSpriteFrame();
			allframe1.pushBack(frame1);
		}
		Animation* an1 = Animation::createWithSpriteFrames(allframe1, 0.1);
		sp1->setPosition(x->getImg()->getPosition());
		sp1->setScale(1.5);
		addLayer(sp1);
		auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(PeaShooter::clear, this));
		Sequence *sequence1 = Sequence::create(Animate::create(an1), CCDelayTime::create(1.3), actionDone1, NULL);
		sp1->runAction(sequence1);
		//对僵尸加buff
		for (auto y : readyZombies)
		{
			y->getDebuff()->push_back(AttackToZero);
			auto actionDone2 = CallFuncN::create(CC_CALLBACK_1(WhiteJannu::cleanBuff, this, y));
			Sequence *sequence2 = Sequence::create(CCDelayTime::create(3), actionDone2, NULL);
			y->getImg()->runAction(sequence2);
		}
	}
	//完成加血加buff

	//延时清除buff，血是永久加的
}

void WhiteJannu::cleanBuff(Node * pSender,Zombie* zombie)
{
	std::cout << "11111" << std::endl;
	//移除debuff
	for (int i = 0; i < zombie->getDebuff()->size(); i++)
	{
		if (zombie->getDebuff()->at(i) == AttackToZero)
		{
			zombie->getDebuff()->erase(zombie->getDebuff()->begin() + i);
			break;
		}
	}
}

