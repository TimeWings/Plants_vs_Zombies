#include "ProgressBar.h"
#include "EntityLayer.h"
#include "UILayer.h"

ZombieProgressBar* ZombieProgressBar::instance = nullptr;

ZombieProgressBar::ZombieProgressBar(Point position)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	sprite = Sprite::create("UI\\LoadingBar0.png");
	sprite->retain();
	sprite->setPosition(position);
	//sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setScale(2.5f);
	//EntityLayer* layer = EntityLayer::getInstance();
	setImg(sprite);
	auto fillSprite = Sprite::create("UI\\LoadingBar100.png");
	fillSprite->setScale(2.5f);
	timer = CCProgressTimer::create(fillSprite);//创建CCProgressTimer
	timer->setPosition(position);//设置CCProgressTimer位置
	timer->setScale(2.5f);
	timer->setType(kCCProgressTimerTypeBar);//设置类型
	timer->setPercentage(0);//设置当前初始值
	timer->setMidpoint(CCPoint(0, 0));//设置进度开始的位置
	timer->setBarChangeRate(CCPoint(1, 0));//设置进度所占比例
	//Sequence *sequence = Sequence::create(ProgressTo::create(2, 100), actionDone, NULL);
	auto layer = UILayer::getInstance();
	layer->addChild(sprite, 999);
	layer->addChild(timer, 1000);
}


ZombieProgressBar::~ZombieProgressBar()
{
}

void ZombieProgressBar::show()
{
	getImg()->setVisible(true);
}

void ZombieProgressBar::hide()
{
	getImg()->setVisible(false);
}

void ZombieProgressBar::clear()
{
	getImg()->removeFromParent();
	timer->removeFromParent();
	delete instance;
	instance = nullptr;
}

float ZombieProgressBar::getCurrentValue()
{
	return timer->getPercentage();
}

void ZombieProgressBar::setCurrentValue(float value)
{
	timer->setPercentage(value);
}