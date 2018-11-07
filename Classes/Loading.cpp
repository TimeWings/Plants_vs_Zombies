#include "Loading.h"
#include "EntityLayer.h"


Loading::Loading(Point position)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	sprite = Sprite::create("UI\\LoadingBar0.png");
	sprite->retain();
	sprite->setPosition(position);
	//sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setScale(2.0f);
	EntityLayer* layer = EntityLayer::getInstance();
	layer->addChild(sprite);
	setImg(sprite);
	auto fillSprite = Sprite::create("UI\\LoadingBar100.png");
	fillSprite->setScale(2.0f);
	timer = CCProgressTimer::create(fillSprite);//创建CCProgressTimer
	timer->setPosition(position);//设置CCProgressTimer位置
	timer->setScale(2.0f);
	timer->setType(kCCProgressTimerTypeBar);//设置类型
	timer->setPercentage(0);//设置当前初始值
	timer->setMidpoint(CCPoint(0, 0));//设置进度开始的位置
	timer->setBarChangeRate(CCPoint(1, 0));//设置进度所占比例
	layer->addChild(timer);
}


Loading::~Loading()
{
}

float Loading::getCurrentValue()
{
	return timer->getPercentage();
}

void Loading::setCurrentValue(float value)
{
	timer->setPercentage(value);
}