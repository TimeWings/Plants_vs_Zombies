#include "PotatoMine.h"
#include "PotatoBullet.h"
#include "Global.h"
#include <iostream>



PotatoMine::PotatoMine(Point position, int row,int col)
{
	this->maxHp = 10;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("PotatoMine\\1.1.png"));
	this->setImg(sp);
	this->birthDelay = 5;

	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(Point(position.x, position.y - this->getImg()->getContentSize().height * this->getImg()->getScaleY() / 5));
	this->setHp(this->maxHp);
	this->setInterval(1000);
	this->position = Point(position.x, position.y - this->getImg()->getContentSize().height * this->getImg()->getScaleY() / 5);
	//延迟出生
	CCDelayTime* delayTime = CCDelayTime::create(this->birthDelay);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::Born_Animation, this));
	Sequence *sequence = Sequence::create(delayTime, actionDone, NULL);
	sp->runAction(sequence);
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}


bool PotatoMine::isWorking()
{
	return true;
}

void PotatoMine::work()
{
	//检测碰撞在前
	if (bornFinish)
	{
		for (int i = 0; i < readyZombies.size(); i++)
		{
			Zombie* zombie = readyZombies.at(i);
			if (this->getRow() == zombie->getRow() && this->getImg()->boundingBox().intersectsRect(zombie->getImg()->getBoundingBox()))
			{
				if (strcmp(typeid(*zombie).name(), "class PoleVaultingZombie") == 0)
				{
					Vec2 pointA = this->getImg()->getPosition();
					Vec2 pointB = zombie->getImg()->getPosition();
					float distance = sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2));
					if (distance > map::BlockSize.first*0.8)
					{
						continue;
					}
				}
				std::cout << "有敌人！爆炸！" << std::endl;
				CreateBullet();
				Die();
				break;
			}
		}
	}
}

void PotatoMine::Die()
{
	clear(this->getImg());
}

void PotatoMine::removeSprite(Node *pSender)
{
	std::cout << "精灵移除" << std::endl;
	pSender->removeFromParent();
}

void PotatoMine::Self_Animation()
{
	if (this->bornFinish)
	{
		std::cout << "哈桑闪闪发光" << std::endl;
		SpriteFrame *sp;
		Vector<SpriteFrame*> allframe;
		char str[100] = { 0 };
		for (int i = 8; i <= 13; i++)
		{
			sprintf(str, "PotatoMine\\%d.1.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		for (int j = 13; j >= 8; j--)
		{
			sprintf(str, "PotatoMine\\%d.1.png", j);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
		this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
	}
}
//出生动画
void PotatoMine::Born_Animation(Node *pSender)
{
	std::cout << "哈桑准备出土" << std::endl;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	SpriteFrame *sp;
	for (int i = 2; i <= 8; i++)
	{
		sprintf(str, "PotatoMine\\%d.1.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::afterBornHandle, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	this->getImg()->runAction(sequence);
}
void PotatoMine::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}
//出生之后的应有的操作
void PotatoMine::afterBornHandle(Node *pSender)
{
	//设置长成bool值
	this->bornFinish = true;
	//重新定义精灵图片
	this->getImg()->removeFromParent();
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("PotatoMine\\9.1.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(this->position);
	//添加到植物层
	addLayer(sp);
	Self_Animation();
}

//产生隐形的子弹
void PotatoMine::CreateBullet()
{
	if (this->bornFinish)
	{
		std::cout << "哈桑爆炸" << std::endl;
		//马上移除容器并消除精灵
		clear(this->getImg());
		//定义爆炸效果
		auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("PotatoMine\\Explode1.png"));
		sp->retain();
		sp->setScale(0.6);
		sp->setPosition(Point(position.x + 10, position.y + 20));
		addLayer(sp);
		//爆炸动画
		char str[100] = { 0 };
		Vector<SpriteFrame*> allframe;
		for (int i = 2; i <= 4; i++)
		{
			sprintf(str, "PotatoMine\\Explode%d.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.2);
		//播放完动画之后消除精灵
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::removeSprite, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		sp->runAction(sequence);
	}
	//产生爆炸弹
	std::cout << "产生子弹" << std::endl;
	Sprite *sp = this->getImg();
	//产生坐标
	Point a = ccp(sp->getPositionX()+sp->getContentSize().width/2*sp->getScaleX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	//只需要new一颗自己的子弹就行
	Bullet *pb = new PotatoBullet(a,this->getRow());
}

void PotatoMine::clear(Node *pSender)
{
	std::cout << "容器移除" << std::endl;
	pSender->removeFromParent();
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	this->setHp(-1);
}