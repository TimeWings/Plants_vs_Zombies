#include "Shovel.h"
#include "Global.h"
#include <iostream>
using namespace map;
Shovel::Shovel(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Shovel.png"));
	this->setImg(sp);
	sp->retain();
	//sp->setScale(1);
	sp->setPosition(position);
	this->setHp(2000);
	this->setInterval(0);
	addLayer(sp);
	this->Self_Animation();
	readyPlants.push_back(this);
}

bool Shovel::isWorking()
{
	return true;
}

void Shovel::work()
{
	PlantStatus* plantstatus = find(this->getRow(), this->getCol());
	if (plantstatus != NULL)
	{
		while (plantstatus->plantVector.size() != 0)
		{
			RemoveRegister(plantstatus->plantVector.front());
		}
	}
}

void Shovel::Self_Animation()
{
}

void Shovel::Attacked()
{
}
