#include "WaterBullet.h"
#include "Global.h"

WaterBullet::WaterBullet(Point position, int Plant_row)
{
	this->getRange()->push_back(Plant_row);
	this->setDamage(1);
	this->setSpeed(6);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("WaterShooter\\WaterBullet1.png"));
	this->setImg(sp);
	sp->setTag(En_Burn);
	sp->retain();
	sp->setScale(3);
	sp->setPosition(position.x, position.y);
	this->addLayer(sp);
	this->move();
	this->attack_Animation();
	readyBullet.push_back(this);
}

void WaterBullet::Hit_Animation(Zombie * zombie)
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
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clearNode, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);

}

void WaterBullet::attack_Animation()
{
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str, "WaterShooter\\WaterBullet%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
}
