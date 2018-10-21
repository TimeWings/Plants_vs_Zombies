#include "Pumpkin.h"
#include "Global.h"
#include <iostream>

Pumpkin::Pumpkin(Point position)
{
	this->position = position;
	this->attackRange = 50.0f;
	this->jumpDuration = 1.0f;
	this->isJumping = false;

	Sprite*sp = Sprite::create("Pumpkin.png");
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(0);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

bool Pumpkin::isWorking()
{
	return true;
}

void Pumpkin::work()
{
	//schedule(schedule_selector(Pumpkin::CheckZombies), 0.1);
	CheckZombies();
}

void Pumpkin::CheckZombies()
{
	for (int i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i)->getImg()->getPositionX() - this->position.y <= this->attackRange && !this->isJumping)
		{
			this->isJumping = true;
			std::cout << "宝具践踏！" << std::endl;
			Trample(readyZombies.at(i));
			readyZombies.erase(readyZombies.begin() + i);
			break;
		}
	}
}

void Pumpkin::Trample(Zombie* zombie)
{
	//移动到僵尸上方，自身放大
	std::cout << "我跳！" << std::endl;
	Point p = Point(zombie->getImg()->getPositionX() - this->jumpDuration*zombie->getWalkSpeed(),this->position.y + 50);
	float height = 0;
	CCActionInterval * jumpto = CCJumpTo::create(this->jumpDuration, p, height, 1);
	this->getImg()->runAction(jumpto);
	//下落
	//僵尸被压扁
}

void Pumpkin::Die()
{
}

void Pumpkin::Self_Animation()
{

}

void Pumpkin::Attacked()
{
}

void Pumpkin::clear(Node * pSender)
{
}
