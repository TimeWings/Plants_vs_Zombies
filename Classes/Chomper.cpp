#include "Chomper.h"
#include "Global.h"
Chomper::Chomper(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Chomper\\Self_Animation\\1.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position.x+10,position.y);
	this->setHp(600);
	this->setInterval(3000);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

bool Chomper::isWorking()
{
	return !isEating;
}

void Chomper::work()
{
	if (isWorking())
	{
		for (int i = 0; i < readyZombies.size(); i++)
		{
			Zombie*zombie = readyZombies.at(i);
			auto sp_zombie = zombie->getImg();
			auto sp_plant = this->getImg();
			if (zombie->getRow() == this->getRow() && sp_zombie->boundingBox().intersectsRect(sp_plant->getBoundingBox()))
			{
				Eat(zombie);
				return;
			}
		}
	}
	
}
void Chomper::Eat(Zombie*zombie)
{
	isEating = true;
	auto sp = zombie->getImg();
	for (int i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i) == zombie)
		{
			readyZombies.erase(readyZombies.begin() + i);
			break;
		}
	}
	//播放攻击和吃东西的动画
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe1;
	for (int i = 1; i <= 9; i++)
	{
		sprintf(str, "Chomper\\Attack\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe1.pushBack(frame);
	}
	Animation* an1 = Animation::createWithSpriteFrames(allframe1, 0.1);
	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(Chomper::clear1, this,sp));
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 6; i++)
	{
		sprintf(str, "Chomper\\Eat\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an2 = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Chomper::resume, this));
	Sequence *sequence = Sequence::create(Animate::create(an1), actionDone1,Repeat::create(Animate::create(an2),5), actionDone, NULL);
	Director::getInstance()->getActionManager()->removeAllActionsByTag(self_tag, this->getImg());
	this->getImg()->runAction(sequence);
}
void Chomper::resume(Node* pSender)
{
	isEating = false;
	this->Self_Animation();
}
void Chomper::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	Sprite * sp = this->getImg();
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Chomper::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void Chomper::Self_Animation()
{
	//播放自身动画
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe1;
	for (int i = 1; i <= 13; i++)
	{
		sprintf(str, "Chomper\\Self_Animation\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe1.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe1, 0.2);
	auto animation = RepeatForever::create(Animate::create(an));
	animation->setTag(self_tag);
	this->getImg()->runAction(animation);
}

void Chomper::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}


void Chomper::clear(Node * pSender)
{
	pSender->removeFromParent();
}
void Chomper::clear1(Node * pSender,Sprite* sp)
{
	sp->getActionManager()->removeAllActionsFromTarget(sp);
	sp->removeFromParent();
}
