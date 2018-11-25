#include "Torch.h"
#include "Global.h"
#include "FireBullet.h"
#include <iostream>
Torch::Torch(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Torch\\1.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(2.5);
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(0);
	addLayer(sp);
	this->Self_Animation();
	readyPlants.push_back(this);
}

bool Torch::isWorking()
{
	return false;
}

void Torch::work()
{
	for (int i = 0; i < readyBullet.size(); i++)
	{
		Bullet*bullet = readyBullet.at(i);
		Sprite * sp = bullet->getImg();
		if (sp->getTag()== En_Burn&&sp->boundingBox().intersectsRect(this->getImg()->getBoundingBox())&&(sp->getPositionY()>this->getImg()->getPositionY()))
		{
			sp->removeFromParent();
			for (int i = 0; i < readyBullet.size(); i++)
			{
				if (readyBullet.at(i) == bullet)
				{
					readyBullet.erase(readyBullet.begin() + i);
					break;
				}
			}
			CreateBullet(bullet);
		}
	}
}


void Torch::Self_Animation()
{
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 9; i++)
	{
		sprintf(str, "Torch\\Self_Animation\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.2);
	this->getImg()->runAction(RepeatForever::create(Animate::create(an)));
}

void Torch::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

void Torch::CreateBullet(Bullet*bullet)
{
	new FireBullet(this->getRow(),bullet,this->getImg()->getContentSize().width*this->getImg()->getScaleX());
}
