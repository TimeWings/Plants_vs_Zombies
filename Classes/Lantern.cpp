#include "Lantern.h"
#include "Global.h"
#include "Background.h"
#include <iostream>
Lantern::Lantern(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Lantern\\Self_Animation\\1.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(1.5);
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

bool Lantern::isWorking()
{
	if (Background::type == 2)
	{
		return true;
	}
	return false;
}

void Lantern::work()
{
	if (isWorking()&&!isLightUp)
	{
		std::cout << "开灯" << std::endl;
		isLightUp = true;
		maskImg = Sprite::create("CircleMask.png");
		maskImg->setScale(2);
		maskImg->setPosition(this->getImg()->getPosition());
		Background::holesStencil->addChild(maskImg);
		//maskImg->removeFromParent();
	}
}

void Lantern::Self_Animation()
{
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 19; i++)
	{
		sprintf(str, "Lantern\\Self_Animation\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto animation = RepeatForever::create(Animate::create(an));
	this->getImg()->runAction(animation);
}

void Lantern::Attacked()
{
	Sprite *sp = this->getImg();
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	float preScale = sp->getScaleX();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
	if (preScale < 0.1) return;
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale - 0.015, preScale - 0.015);
	sp->runAction(scaledown);
}

void Lantern::clear(Node * pSender)
{
	pSender->removeFromParent();
	if (maskImg != NULL)
	{
		std::cout << "asfjkf" << std::endl;
		maskImg->removeFromParent();
	}
}
