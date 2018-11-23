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
	EntityLayer* bl = EntityLayer::getInstance();
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

		sp->setPosition(Point(x->getImg()->getContentSize().width / 2, x->getImg()->getContentSize().height / 2));

		sp->setScaleX(x->getImg()->getContentSize().width / sp->getContentSize().width);
		sp->setScaleY(x->getImg()->getContentSize().height / sp->getContentSize().height);

		x->getImg()->addChild(sp);
		//bl->addChild(sp, x->getRow() * 3 - 3);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(WhiteJannu::clearNode, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		sp->runAction(sequence);
		//加血5点
		if (x->getHp() < 20)
		{
			x->setHp(x->getHp() + 5);
		}
		
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
		sp1->setPosition(Point(x->getImg()->getContentSize().width / 2, x->getImg()->getContentSize().height / 2));
		sp1->setScaleX(x->getImg()->getContentSize().width / sp1->getContentSize().width);
		sp1->setScaleY(x->getImg()->getContentSize().height / sp1->getContentSize().height);
		x->getImg()->addChild(sp1);
		//bl->addChild(sp1, x->getRow() * 3 - 3);
		auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(WhiteJannu::clearNode, this));
		auto actionDone2 = CallFuncN::create(CC_CALLBACK_1(WhiteJannu::cleanBuff, this, x));
		Sequence *sequence1 = Sequence::create(Animate::create(an1), CCDelayTime::create(1.3), actionDone1, actionDone2, NULL);
		sp1->runAction(sequence1);
		//加buff
		x->getbuff()->push_back(Invincible);
	}
}

void WhiteJannu::cleanBuff(Node * pSender,Plants* plant)
{
	//移除debuff
	for (int i = 0; i < plant->getbuff()->size(); i++)
	{
		if (plant->getbuff()->at(i) == Invincible)
		{
			plant->getbuff()->erase(plant->getbuff()->begin() + i);
			break;
		}
	}
}

