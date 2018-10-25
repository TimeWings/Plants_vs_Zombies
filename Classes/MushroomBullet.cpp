#include "MushroomBullet.h"
#include "Global.h"
#include <iostream>

MushroomBullet::MushroomBullet(Point position, int Plant_row)
{
	this->getRange()->push_back(Plant_row);
	Sprite *sp = Sprite::create("snake1.png");
	//方便以后获取子弹精灵
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position.x + sp->getContentSize().width*sp->getScaleX() / 1.3, position.y);
	this->addLayer(sp);
	this->attack_Animation();
}

void MushroomBullet::move()
{
}

void MushroomBullet::clear(Node * pSender)
{
	pSender->removeFromParent();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
}

void MushroomBullet::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}
//播放攻击动画
void MushroomBullet::attack_Animation()
{
	SpriteFrame *sp;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	for (int i = 1; i <= 7; i++)
	{
		sprintf(str, "snake%d.png", i);
		sp = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(sp);
	}
	for (int j = 7; j >= 1; j--)
	{
		sprintf(str, "snake%d.png", j);
		sp = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(sp);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
}
//僵尸被攻击动画
void MushroomBullet::Hit_Animation(Zombie * zombie)
{
	Sprite* sp = this->getImg();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
	ActionInterval * fadeout = FadeOut::create(0.3);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(MushroomBullet::clearNode, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}
