#include "PeaBulletPlus.h"
#include <math.h>
#include "Global.h"
#include <iostream>

PeaBulletPlus::PeaBulletPlus()
{
}

PeaBulletPlus::PeaBulletPlus(Point position, int Plant_row, double angle,double distance)
{
	this->_distance = distance;
	this->_angle = angle;
	for (int i = 0; i < 10; i++)
	{
		this->getRange()->push_back(i);
	}
	auto sp = Sprite::create("StarBullet.png");
	if (angle == -90 || angle == 90 || angle == 180)
	{
		sp->setTag(Pitcher_tag);
	}
	sp->setRotation(-angle);
	sp->setScale(0.2);
	this->setDamage(1);
	this->setSpeed(70);
	//方便以后获取子弹精灵
	this->setImg(sp);
	sp->retain();
	sp->setPosition(position);
	this->addLayer(sp);
	readyBullet.push_back(this);
	//移动函数
	this->move();
}
void PeaBulletPlus::move()
{
	Point a;
	auto sp = this->getImg();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//double xie = sqrt(visibleSize.width*visibleSize.width + visibleSize.height*visibleSize.height);
	a.x = sp->getPositionX() + _distance *cos(_angle / 180 * std::_Pi);
	a.y = sp->getPositionY() + _distance *sin(_angle / 180 * std::_Pi);
	double distance =sqrt(pow((sp->getPositionX()-a.x),2)+pow((sp->getPositionY() - a.y), 2));
	double time = distance / getSpeed();
	MoveTo *moveTo = MoveTo::create(time, a);
	//MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width-50, sp->getPosition().y));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clear, this));
	//动画序列顺序播放
	CCRotateBy* rotate = CCRotateBy::create(time, 1200);
	CCSpawn* spawn = CCSpawn::create(rotate, moveTo, NULL);
	Sequence *sequence = Sequence::create(spawn, actionDone, NULL);
	sp->runAction(sequence);

}

void PeaBulletPlus::clear(Node * pSender)
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

