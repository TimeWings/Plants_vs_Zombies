#include "Cushaw.h"
#include "Global.h"

Cushaw::Cushaw(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("cushaw.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(3);
	sp->setPosition(position);
	this->setHp(25);
	this->setInterval(0);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

void Cushaw::Attacked()
{
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	this->getImg()->runAction(sequence);
	if (this->getHp() < 5)
	{
		auto sprite = Sprite::create("cushaw_2.png");
		this->getImg()->setTexture(sprite->getTexture());
	}
	else if (this->getHp() < 15)
	{
		auto sprite = Sprite::create("cushaw_1.png");
		this->getImg()->setTexture(sprite->getTexture());
	}
}
