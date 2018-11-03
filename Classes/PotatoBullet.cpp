#pragma once
#include "cocos2d.h"
#include "Global.h"
#include "PotatoBullet.h"
#include <iostream>
USING_NS_CC;

PotatoBullet::PotatoBullet(Point position, int Plant_row):Bullet(position,50,0)
{
	this->getRange()->push_back(Plant_row);
	auto* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("none.png"));
	this->setImg(sp);
	sp->setScale(0.1);
	sp->retain();
	sp->setPosition(position.x + sp->getContentSize().width * sp->getScaleX() / 2, position.y);
	this->addLayer(sp);
	readyBullet.push_back(this);
}

void PotatoBullet::move()
{
}

void PotatoBullet::clear(Node * pSender)
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

void PotatoBullet::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}

void PotatoBullet::Hit_Animation(Zombie* zombie)
{
	//±¬Õ¨×Ö
	std::cout << "×Óµ¯Åöµ½½©Ê¬" << std::endl;
	Sprite* sp = this->getImg();
	clearNode(sp);
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}	
	
}
