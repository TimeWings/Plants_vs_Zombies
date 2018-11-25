#include "Lotus.h"
#include "Global.h"
Lotus::Lotus(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Lotus\\Self_Animation\\1.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position.x,position.y-1.3*sp->getContentSize().height);
	this->setHp(6);
	this->setInterval(0);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

bool Lotus::isWorking()
{
	return false;
}

void Lotus::work()
{
	PlantStatus* plantstatus = map::find(this->getRow(), this->getCol());
	if (plantstatus != NULL)
	{
		for (int i = 0; i < plantstatus->plantVector.size(); i++)
		{
			Plants* x = plantstatus->plantVector.at(i);
			if (strcmp(typeid(*x).name(), "class Lotus") == 0&&i!= plantstatus->plantVector.size()-1)
			{
				plantstatus->plantVector.erase(plantstatus->plantVector.begin() + i);
				plantstatus->plantVector.push_back(this);
				break;
			}
		}
	}
}

void Lotus::Self_Animation()
{
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 3; i++)
	{
		sprintf(str, "Lotus\\Self_Animation\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.2);
	auto animation = RepeatForever::create(Animate::create(an));
	this->getImg()->runAction(animation);
}

void Lotus::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}
