#include "PotatoMine.h"
#include "PotatoBullet.h"
#include "Global.h"
#include <iostream>



PotatoMine::PotatoMine(Point position)
{
	Sprite*sp = Sprite::create("1.1.png");
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	this->position = position;
	//延迟出生
	CCDelayTime* delayTime = CCDelayTime::create(1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::Born_Animation, this, position));
	Sequence *sequence = Sequence::create(delayTime, actionDone, NULL);
	sp->runAction(sequence);
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

bool PotatoMine::isWorking()
{
	return false;
}

void PotatoMine::work()
{
}

void PotatoMine::Die()
{
	std::cout << "哈桑爆炸" << std::endl;
	//马上移除容器并消除精灵
	clear(this->getImg());
	//定义爆炸效果
	Sprite* sp = Sprite::create("Explode1.png");
	sp->retain();
	sp->setScale(0.6);
	sp->setPosition(this->position);
	addLayer(sp);
	//爆炸动画
	SpriteFrame *sp1;
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 2; i <= 4; i++)
	{
		sprintf(str, "Explode%d.png", i);
		sp1 = SpriteFrame::create(str, Rect(0, 0, 150, 100));
		allframe.pushBack(sp1);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.2);
	//播放完动画之后消除精灵
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::removeSprite, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);
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
			sprintf(str, "%d.1.png", i);
			sp = SpriteFrame::create(str, Rect(0, 0, 90, 70));
			allframe.pushBack(sp);
		}
		for (int j = 13; j >= 8; j--)
		{
			sprintf(str, "%d.1.png", j);
			sp = SpriteFrame::create(str, Rect(0, 0, 90, 70));
			allframe.pushBack(sp);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
		this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
	}
}

void PotatoMine::Born_Animation(Node *pSender, Point position)
{
	std::cout << "哈桑准备出土" << std::endl;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	SpriteFrame *sp;
	for (int i = 2; i <= 7; i++)
	{
		sprintf(str, "%d.1.png", i);
		sp = SpriteFrame::create(str, Rect(0, 0, 90, 70));
		allframe.pushBack(sp);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::afterBornHandle, this, position));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	this->getImg()->runAction(sequence);
}
//出生之后的应有的操作
void PotatoMine::afterBornHandle(Node *pSender,Point position)
{
	//设置长成bool值
	//std::cout << "出生完成"<<std::endl;
	this->bornFinish = true;
	//重新定义精灵图片
	this->getImg()->removeFromParent();
	Sprite* sp = Sprite::create("8.1.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(position);
	//添加到植物层
	addLayer(sp);
	//播放眨眼动画
	Self_Animation();
}

//被攻击时的操作
void PotatoMine::Attacked()
{
	if (bornFinish)
	{
		CreateBullet();
		Die();
	}
}	
//产生隐形的子弹
void PotatoMine::CreateBullet()
{
	//产生爆炸弹
	std::cout << "产生子弹" << std::endl;
	Sprite *sp = this->getImg();
	//产生坐标
	Point a = ccp(sp->getPositionX()+sp->getContentSize().width/2*sp->getScaleX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	//只需要new一颗自己的子弹就行
	Bullet *pb = new PotatoBullet(a);
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
}