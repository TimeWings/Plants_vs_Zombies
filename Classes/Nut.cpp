#include "Nut.h"
#include "Global.h"
Nut::Nut(Point position, int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Nut1.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.31);
	sp->setPosition(position);
	this->setHp(12);
	this->setInterval(0);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

Nut::Nut()
{
}

bool Nut::isWorking()
{
	return true;
}

void Nut::work()
{
}

void Nut::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	Sprite * sp = this->getImg();
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Nut::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void Nut::Self_Animation()
{
	Sprite *sp = this->getImg();
	//float preScale = sp->getScaleX();
	CCScaleBy * scaleup = CCScaleBy::create(0.7f, 0.8, 1.25);
	CCScaleBy * scaledown = CCScaleBy::create(0.3f, 1.25, 0.8);
	Sequence *sequence = Sequence::create(scaleup, scaledown, NULL);
	sp->runAction(CCRepeatForever::create(sequence));
}

void Nut::Attacked()
{
	Sprite *sp = this->getImg();
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	float preScale = sp->getScaleX();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
	if (preScale < 0.1) return;
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale-0.015, preScale - 0.015);
	sp->runAction(scaledown);
}

void Nut::clear(Node * pSender)
{
	pSender->removeFromParent();
}
