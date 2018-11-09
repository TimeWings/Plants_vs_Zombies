#include "Thunder.h"
#include "Global.h"
#include <iostream>

Thunder::Thunder(Point position, int row, int col)
{
	this->curDetail = 5;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Thunder\\thunder.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.25);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	this->Self_Animation();
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

void Thunder::work()
{
	if (isWorking())
	{
		creatSprite();
	}
}

void Thunder::creatSprite()
{
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		if (zombie->getRow() == this->getRow())
		{
			ccDrawColor4B(255, 0, 0, 0);
			glLineWidth(2);
			createThunder(this->getImg()->getPositionX(), this->getImg()->getPositionY(), zombie->getImg()->getPositionX(), zombie->getImg()->getPositionY(), 200);
		}
	}
}

void Thunder::createThunder(float x1, float y1, float x2, float y2, float displace)
{
	if (displace < curDetail)
	{
		ccDrawLine(ccp(x1, y1), ccp(x2, y2));
	}
	else
	{
		float mid_x = (x2 + x1) / 2;
		float mid_y = (y2 + y1) / 2;
		mid_x += (CCRANDOM_0_1() - 0.5) * displace;
		mid_y += (CCRANDOM_0_1() - 0.5) * displace;
		createThunder(x1, y1, mid_x, mid_y, displace / 2);
		createThunder(x2, y2, mid_x, mid_y, displace / 2);
	}
}
