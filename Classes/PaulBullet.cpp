#include "PaulBullet.h"
#include "Global.h"

//传进来的是目的地址的坐标
PaulBullet::PaulBullet(Point position, double delayTime)
{
	this->delayTime = delayTime;
	this->position = position;
	this->setRow(map::Point2Rank(position).first);
	this->setRow(map::Point2Rank(position).second);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\LancerBullterDown.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	//获取屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//在屏幕上方生成子弹
	sp->setPosition(Point(position.x, visibleSize.height + sp->getContentSize().height / 2));
	addLayer(sp);
	this->work();
}

void PaulBullet::move()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double time = (visibleSize.height + this->getImg()->getScaleY() / 2) / speed;
	//移动到目的坐标
	MoveTo *moveTo = MoveTo::create(time, position);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PaulBullet::Effect, this));
	Sequence *sequence = Sequence::create(CCDelayTime::create(this->delayTime), moveTo, actionDone, NULL);
	this->getImg()->runAction(sequence);
}

void PaulBullet::work()
{
	this->move();
}

void PaulBullet::zombiesDie()
{
	//清除范围内僵尸
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		//判断范围
		if (pow(zombie->getImg()->getPositionX() - this->position.x, 2) + pow(zombie->getImg()->getPositionY() - this->position.y, 2) <= 90 * 90)
		{
			Sprite* pSender = readyZombies.at(i)->getImg();
			//记录下原本僵尸的必要信息
			Point zombiePoint = pSender->getPosition();
			float scale = pSender->getScaleX();
			//停止僵尸所有动作
			pSender->removeFromParent();
			pSender->removeAllChildrenWithCleanup(true);
			//僵尸粉碎动画
			char str[100] = { 0 };
			Vector<SpriteFrame*> allframe;
			for (int i = 2; i <= 20; i++)
			{
				sprintf(str, "Boom_Die\\Boom_Die%d.png", i);
				auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
				auto frame = sprite->getSpriteFrame();
				allframe.pushBack(frame);
			}
			Animation* an = Animation::createWithSpriteFrames(allframe, 0.15);
			auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Boom_Die\\Boom_Die1.png"));
			sp->setPosition(zombiePoint);
			sp->retain();
			sp->setScale(scale);
			addLayer(sp);
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::clear, this));
			Sequence *sequence = Sequence::create(Animate::create(an), CCDelayTime::create(0.5), actionDone, NULL);
			sp->runAction(sequence);
			//移除数组
			readyZombies.erase(readyZombies.begin() + i);
			i--;
		}
	}
}

void PaulBullet::creatSprite()
{
	//爆炸动画
	SpriteFrame *sp1;
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 11; i++)
	{
		sprintf(str, "Cannon\\Boom\\BoomSmall%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\Boom\\BoomSmall1.png"));
	sp->retain();
	sp->setScale(3);
	sp->setPosition(Point(this->position.x, this->position.y + 20));
	addLayer(sp);
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::clearSprite, this, sp));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);
}
