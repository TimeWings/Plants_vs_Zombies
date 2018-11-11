#include "HeroThunder.h"
#include "Global.h"

HeroThunder::HeroThunder(Point position, int row, int col)
{
	this->hasThunder = false;
	this->curtentDamage = 2;
	this->thunderHeight = 3;
	this->setRow(row);
	this->setCol(col);
	this->currentCol = col;
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("HeroThunder\\HeroThunder.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	this->Self_Animation();
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
	this->lastPoint = this->getImg()->getPosition();
}

bool HeroThunder::isWorking()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto x : readyZombies)
	{
		if (x->getImg()->getPositionX() < visibleSize.width)
		{
			return true;
		}
	}
	return false;
}

void HeroThunder::work()
{
	if (isWorking())
	{
		creatSprite();
	}
}

void HeroThunder::creatSprite()
{
	//复制readyZombie数组
	std::vector<Zombie*> zombieSet = readyZombies;
	//把原本的数组按X轴排序
	std::vector<Zombie*> zombieSetSorted;
	Zombie* min;
	int NO;
	for (int i = 0; i < zombieSet.size();)
	{
		Zombie* zombie = zombieSet.at(i);
		min = zombie;
		NO = 0;
		for (int j = 1; j < zombieSet.size(); j++)
		{
			if (map::Point2Rank(min->getImg()->getPosition()).second > map::Point2Rank(zombieSet.at(j)->getImg()->getPosition()).second)
			{
				min = zombieSet.at(j);
				NO = j;
			}
		}
		zombieSetSorted.push_back(min);
		zombieSet.erase(zombieSet.begin() + NO);
	}

	for (int i = 0; i < zombieSetSorted.size(); i++)
	{
		Zombie* zombie = zombieSetSorted.at(i);
		if (zombie->getImg()->getPositionX() > this->getImg()->getPositionX())
		{
			if (!this->hasThunder)
			{
				this->hasThunder = true;
				createThunder(
					Point(this->getImg()->getPosition().x + this->getImg()->getContentSize().width * this->getImg()->getScaleX() / 2.5, this->getImg()->getPositionY() + this->getImg()->getContentSize().height * this->getImg()->getScaleY() / 2),
					Point(zombie->getImg()->getPosition().x, zombie->getImg()->getPosition().y),
					zombie);
			}
			else
			{
				createThunder(this->lastPoint, zombie->getImg()->getPosition(), zombie);
			}
			this->lastPoint = zombie->getImg()->getPosition();
			zombie->DamageBoth(curtentDamage);
		}
		
	}
	this->lastPoint = this->getImg()->getPosition();
	this->hasThunder = false;
	setNewBirthTime();
}
