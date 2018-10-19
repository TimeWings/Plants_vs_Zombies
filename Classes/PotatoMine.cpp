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

	//延迟出生
	CCDelayTime* delayTime = CCDelayTime::create(15);
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
	//到时候要爆炸

	std::cout << "哈桑爆炸" << std::endl;
	clear(this->getImg());
}

void PotatoMine::Self_Animation()
{
	
	if (this->bornFinish)
	{
		std::cout << "哈桑眼睛闪闪发光" << std::endl;
		SpriteFrame *sp;
		Vector<SpriteFrame*> allframe;
		sp = SpriteFrame::create("8.1.png", Rect(0, 0, 90, 70));
		allframe.pushBack(sp);
		sp = SpriteFrame::create("9.1.png", Rect(0, 0, 90, 70));
		allframe.pushBack(sp);
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.5);
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

void PotatoMine::afterBornHandle(Node *pSender,Point position)
{
	//设置长成bool值
	std::cout << "出生完成"<<std::endl;
	this->bornFinish = true;
	this->getImg()->removeFromParent();
	Sprite* sp = Sprite::create("8.1.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(position);
	//添加到植物层
	addLayer(sp);
	Self_Animation();
}

void PotatoMine::Attacked()
{
	if (bornFinish)
	{
		CreateBullet();
		Die();
	}
}	

void PotatoMine::CreateBullet()
{

	//产生爆炸弹
	Sprite *sp = this->getImg();
	Point a = ccp(sp->getPositionX()+sp->getContentSize().width/2*sp->getScaleX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	Bullet *pb = new PotatoBullet(a);
	
}

void PotatoMine::clear(Node *pSender)
{
	//std::cout << "闪闪死亡" << std::endl;
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