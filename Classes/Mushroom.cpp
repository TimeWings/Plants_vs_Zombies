#include "Mushroom.h"
#include "MushroomBullet.h"
#include "Global.h"
#include <iostream>

Mushroom::Mushroom()
{
}

Mushroom::Mushroom(Point position, int row,int col)
{
	this->haveBullet = false;
	this->attackCol = 3;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Mushroom\\Mushroom.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.22);
	this->Scale = this->getImg()->getScale();
	sp->setPosition(position);
	this->setHp(10);
	this->setInterval(2000);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}
bool Mushroom::isWorking()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto x : readyZombies)
	{
		if (this->getRow() == x->getRow() && x->getImg()->getPositionX() < visibleSize.width 
			&& map::Point2Rank(x->getImg()->getPosition()).second - this->getCol() <= attackCol
			&& x->getImg()->getPositionX() > this->getImg()->getPositionX())
		{
			return true;
		}
	}
	return false;
}
//产生子弹的动画
void Mushroom::CreateBullet()
{
	if (!this->haveBullet)
	{
		this->haveBullet = true;
		//禁用当前移动的动画
		//Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this->getImg());
		
		//播放产生子弹的动画
		CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
		CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
		CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
		Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
		this->getImg()->runAction(sequence);
		//产生子弹
		Sprite *sp = this->getImg();
		//植物中心点X坐标，植物中心点+1/4植物高度的Y坐标
		Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
		MushroomBullet *pb = new MushroomBullet(a, this->getRow());
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(Mushroom::clearBullet, this));
		//与子弹清除延时一样，用来设置填充时间，回播动画
		Sequence *sequence1 = Sequence::create(CCDelayTime::create(1), actionDone, NULL);
		this->getImg()->runAction(sequence1);
	}
}

void Mushroom::Self_Animation()
{
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(0.7f, preScale, preScale + 0.05);
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale, preScale);
	Sequence *sequence1 = Sequence::create(scaleup, scaledown, NULL);
	CCActionInterval * moveBy = CCMoveBy::create(1, ccp(7, 0));
	CCActionInterval * actionmoveback = moveBy->reverse();
	CCFiniteTimeAction * spawn1 = CCSpawn::create(sequence1, moveBy, NULL);
	CCFiniteTimeAction * spawn2 = CCSpawn::create(sequence1, actionmoveback, NULL);
	Sequence *sequence2 = Sequence::create(spawn1, spawn2, NULL);
	sp->runAction(CCRepeatForever::create(sequence2));
}

void Mushroom::clearBullet(Node *pSender)
{
	//设置时间
	this->setNewBirthTime();
	this->haveBullet = false;
	//重新播放动画
	//Self_Animation();
}

void Mushroom::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	clear(this->getImg());
}


