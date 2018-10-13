#include "Sunflower.h"
#include "Global.h"
#include <iostream>
Sunflower::Sunflower(Point position)
{
	//std::cout << "太阳花生成" << std::endl;
	Sprite*sp = Sprite::create("sunFlower.png");
	setScale(0.3);
	sp->setScale(getScale());
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(5000);
	prePlants.insert(this, sp);
}

void Sunflower::work(Sprite * sp)
{
	CreateSun(sp);
}

void Sunflower::Die(Sprite * sp)
{
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Sunflower::clear, this, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void Sunflower::init(Sprite * sp)
{
	Self_Animation(sp);
}

void Sunflower::Attacked(Sprite * sp)
{
	CCActionInterval * tintby = CCTintBy::create(0.6, 0, 255, 255);
	sp->runAction(tintby);
}

bool Sunflower::isAttacking()
{
	return false;
}

void Sunflower::Self_Animation(Sprite * sp)
{
	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	ScaleBy * scaleup = ScaleBy::create(0.5f, 1.25f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, NULL);
	sp->runAction(RepeatForever::create(sequence));
}

void Sunflower::CreateSun(Sprite * sp)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *spSun = Sprite::create("sun.png");
	Point a = Point(sp->getPositionX(), sp->getPositionY() + sp->getContentSize().height / 2 * sp->getScale());
	spSun->setPosition(a);
	spSun->setScale(0.5);
	if ((preSun.find(sp) != preSun.end()) || (readySun.find(sp) != readySun.end()))
	{
		return;
	}
	preSun.insert(sp, spSun);

	
    
	
}

void Sunflower::clear(Node * pSender, Plants * plant)
{
	//std::cout << "太阳花死亡" << std::endl;
	pSender->removeFromParent();
	readyPlants.erase(plant);
}


