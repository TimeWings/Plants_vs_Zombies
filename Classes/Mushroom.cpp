#include "Mushroom.h"
#include "MushroomBullet.h"
#include "Global.h"
#include <iostream>

Mushroom::Mushroom(Point position, int row,int col)
{
	this->haveBullet = false;
	this->setRow(row);
	this->setCol(col);
	Sprite*sp = Sprite::create("Mushroom.png");
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.3);
	this->Scale = this->getImg()->getScale();
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(1200);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}
//产生子弹的动画
void Mushroom::CreateBullet()
{
	if (!this->haveBullet)
	{
		this->haveBullet = true;
		//禁用当前移动的动画
		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this->getImg());
		//播放产生子弹的动画
		CCScaleBy * scaleup = CCScaleBy::create(0.1f, 0.8f, 0.8f);
		CCScaleBy * scaledown = CCScaleBy::create(0.1f, 1.5625f, 1.5625f);
		CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 0.8f);
		Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
		this->getImg()->runAction(CCRepeatForever::create(sequence));
		//产生子弹
		Sprite *sp = this->getImg();
		//植物中心点X坐标，植物中心点+1/4植物高度的Y坐标
		Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
		MushroomBullet *pb = new MushroomBullet(a, this->getRow());
		//回调函数，清除子弹，子弹持续时间为5秒;
		CCDelayTime* delayTime = CCDelayTime::create(1);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(Mushroom::clearBullet, this, pb));
		Sequence *sequence1 = Sequence::create(delayTime, actionDone, NULL);
		this->getImg()->runAction(sequence1);
	}
}

void Mushroom::Self_Animation()
{
	Sprite *sp = this->getImg();
	//禁用当前移动的动画
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	//再生成新的移动动画
	sp->setScale(this->Scale);
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

void Mushroom::clear(Node * pSender)
{
	pSender->removeFromParent();
}

void Mushroom::clearBullet(Node *pSender, MushroomBullet *bp)
{
	//消除子弹
	bp->getImg()->removeFromParent();
	bp->clear(bp->getImg());
	//设置时间
	this->setNewBirthTime();
	this->haveBullet = false;
	//重新播放动画
	Self_Animation();
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


