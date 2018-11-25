#include "Ladder.h"
#include "Global.h"
#include "LadderEquip.h"
Ladder::Ladder(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Card\\Ladder.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(1.7);
	sp->setPosition(position.x+map::BlockSize.first/3,position.y);
	this->setHp(2000);
	this->setInterval(0);
	LadderEquip::LadderSprite.pushBack(sp);
	//添加到植物层
	EntityLayer* bl = EntityLayer::getInstance();
	bl->addChild(sp, this->getRow()*3);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

void Ladder::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	for (int i = 0; i < LadderEquip::LadderSprite.size(); i++)
	{
		if (LadderEquip::LadderSprite.at(i) == this->getImg())
		{
			LadderEquip::LadderSprite.erase(LadderEquip::LadderSprite.begin() + i);
		}
	}
	Sprite * sp = this->getImg();
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Ladder::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void Ladder::clear(Node * pSender)
{
	pSender->removeFromParent();
	pSender->removeAllChildrenWithCleanup(true);
	delete this;
}
