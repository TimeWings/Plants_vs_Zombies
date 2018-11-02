#include "TripleBullet.h"
#include "Global.h"
#include <iostream>
using namespace map;
TripleBullet::TripleBullet(Point position, int Plant_row, int type) :Bullet(position, 1, 6)
{
	_type = type;
	auto sp = Sprite::create("TripleBullet.png");
	if (type == 1)
	{
		this->getRange()->push_back(Plant_row);
		this->getRange()->push_back(Plant_row-1);

	}
	else if (type == 2)
	{
		this->getRange()->push_back(Plant_row);
	}
	else
	{
		this->getRange()->push_back(Plant_row);
		this->getRange()->push_back(Plant_row + 1);
	}
	sp->setTag(En_Burn);
	sp->setScale(0.2);
	//方便以后获取子弹精灵
	this->setImg(sp);
	sp->setPosition(position);
	sp->retain();
	this->addLayer(sp);
	//子弹的特效（产生时的特效，或者拖尾效果）
	this->attack_Animation();
	this->Self_Animation();
	readyBullet.push_back(this);
	//移动函数
	this->move();
}
void TripleBullet::Self_Animation()
{
	this->getImg()->runAction(CCRepeatForever::create(CCRotateBy::create(0.1f, 180.0f)));
}
void TripleBullet::move()
{
	Sprite*sp = this->getImg();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double distance = sqrt(map::BlockSize.first*map::BlockSize.first+ map::BlockSize.second*map::BlockSize.second)/15;
	double time = distance / getSpeed();
	Point a;
	if (_type == 1)
	{
		a = Point(sp->getPositionX()+map::BlockSize.first, sp->getPositionY() + BlockSize.second);
	}
	else if (_type == 2)
	{
		a = Point(sp->getPositionX() + map::BlockSize.first, sp->getPositionY());
	}
	else
	{
		a = Point(sp->getPositionX()+BlockSize.first, sp->getPositionY()- BlockSize.second);
	}
	MoveTo *moveTo = MoveTo::create(time, a);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(TripleBullet::afterMove, this));
	Sequence *sequence = Sequence::create(moveTo, actionDone, NULL);
	sp->runAction(sequence);
}
void TripleBullet::afterMove(Node *pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double distance = (visibleSize.width + pSender->getContentSize().width*pSender->getScaleX() - pSender->getPositionX()) / 15;
	double time = distance / getSpeed();
	MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width + pSender->getContentSize().width*pSender->getScaleX(), pSender->getPosition().y));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(TripleBullet::clear, this));
	//动画序列顺序播放
	Sequence *sequence = Sequence::create(moveTo, actionDone, NULL);
	pSender->runAction(sequence);
}
void TripleBullet::clear(Node * pSender)
{
	pSender->removeFromParent();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
}

void TripleBullet::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}

void TripleBullet::attack_Animation()
{
}

void TripleBullet::Hit_Animation(Zombie * zombie)
{
	Sprite* sp = this->getImg();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
	ActionInterval * fadeout = FadeOut::create(0.3);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(TripleBullet::clearNode, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}
