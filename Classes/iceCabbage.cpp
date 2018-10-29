#include "iceCabbage.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>
iceCabbage::iceCabbage(Point position, int row)
{
	this->setRow(row);
	Sprite*sp = Sprite::create("IceCabbage\\IceCabbage.png");
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.3);
	this->position = position;
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	//添加到植物层（显示）
	addLayer(sp);
	//立即调用die
	Die();
}

bool iceCabbage::isWorking()
{
	return true;
}

void iceCabbage::work()
{
}

void iceCabbage::Die()
{
	//梅芙拉伸
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(1.0f, preScale + 0.05, preScale + 0.01);
	//梅芙拉伸和冰雪函数合成队列
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(iceCabbage::iceWorld, this));
	Sequence *sequence = Sequence::create(scaleup, actionDone, NULL);

	sp->runAction(sequence);
}

void iceCabbage::iceWorld(Node *pSender)
{
	//把旧精灵移除
	this->getImg()->removeFromParent();
	//半个地图覆盖冰雪
	Point minPointInX = readyZombies.at(0)->getImg()->getPosition();
	for (int i = 1; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i)->getImg()->getPositionX() < minPointInX.x)
		{
			minPointInX = readyZombies.at(i)->getImg()->getPosition();
		}
	}
	//半个地图覆盖冰雪

	//使僵尸冰冻
	for (int i = 0; i < readyZombies.size(); i++)
	{
		std::cout << "冻结僵尸" << std::endl;
		freezeZombie(readyZombies.at(i));
	}
}

void iceCabbage::freezeZombie(Zombie* zombie)
{
	Point freezePoint = zombie->getImg()->getPosition();
	float scale = zombie->getImg()->getScale();
	//覆盖一层淡蓝色
	CCActionInterval * tintto2 = CCTintTo::create(3, 0, 255, 255);
	zombie->getImg()->runAction(tintto2);
	zombie->getImg()->getActionManager()->removeAllActionsByTag(Animation_Tag, zombie->getImg());
	
	//产生冰冻精灵
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 16; i++)
	{
		sprintf(str, "IceCabbage\\ice%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);

	Sprite*sp = Sprite::create("IceCabbage\\ice16.png");
	sp->setPosition(freezePoint);
	sp->retain();
	sp->setScale(1.4);
	EntityLayer* bl = EntityLayer::getInstance();
	bl->addChild(sp, 100);
	//冰冻时间
	CCDelayTime* delayTime = CCDelayTime::create(3);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(iceCabbage::clearIceSprite, this, sp, zombie));
	Sequence *sequence = Sequence::create(Animate::create(an), delayTime, actionDone, NULL);
	sp->runAction(sequence);
}

void iceCabbage::Attacked()
{
}

void iceCabbage::CreateBullet()
{
}

void iceCabbage::clearIceSprite(Node * pSender, Sprite * iceSprite, Zombie* zombie)
{
	iceSprite->removeFromParent();
	//清除僵尸的蓝色覆盖
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	zombie->getImg()->runAction(tintto2);
	//僵尸恢复行动
	zombie->Move();
}

void iceCabbage::clear(Node * pSender)
{
	pSender->removeFromParent();
}
