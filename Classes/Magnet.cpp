#include "Magnet.h"
#include "Global.h"
#include <iostream>

Magnet::Magnet(Point position, int row, int col)
{
	this->attracted = false;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Magnet\\Magnet.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.25);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(8000);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

bool Magnet::isWorking()
{
	if(!this->attracted)
		return true;
	return false;
}

void Magnet::work()
{
	attractEquiment();
}

void Magnet::Die()
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

void Magnet::CreateBullet()
{
	//NULL
}

void Magnet::attractEquiment()
{
	for (auto x : readyZombies)
	{
		Sprite *sp = x->MagnetEquip();
		if (sp != NULL)
		{
			this->attracted = true;
			//有装备可以吸
			MoveTo *moveTo = MoveTo::create(2, this->getImg()->getPosition());
			CCRotateBy* rotate = CCRotateBy::create(2, 60);
			CCSpawn* spawn = CCSpawn::create(moveTo, rotate,NULL);
			sp->runAction(spawn);
			break;
		}
	}

}
