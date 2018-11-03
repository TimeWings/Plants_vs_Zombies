#include "Lancer.h"
#include "Global.h"
#include "LancerGun.h"
#include <iostream>

Lancer::Lancer(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\Lancer.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	
	//添加到植物层
	this->addLayer(sp);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

void Lancer::CreateBullet()
{
	//放大，准备放子弹
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	//子弹以及僵尸的坐标
	Point a = ccp(this->getImg()->getPositionX(), this->getImg()->getContentSize().height * this->getImg()->getScaleY() / 4 + this->getImg()->getPositionY());
	//产生子弹
	Bullet *pb = new LancerGun(a, this->getRow());
	setNewBirthTime();
}

