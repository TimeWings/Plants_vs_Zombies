#include "Paul.h"
#include "Global.h"
#include "PaulBullet.h"
#include <iostream>

bool Paul::plantSelect = false;

Paul::Paul(Point position, int row, int col)
{
	this->canShoot = true;
	this->shootReady = false;
	this->canSelect = true;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\Connon.png"));
	sp->setTag(Paul_tag);
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(map::BlockSize.first*2 / sp->getContentSize().width);
	sp->setPosition(Point(position.x + map::BlockSize.first / 2, position.y));
	this->setHp(6);
	this->setInterval(5000);
	//添加到植物层
	addLayer(sp);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);

	auto listener = EventListenerTouchOneByOne::create();
	auto listener1 = EventListenerMouse::create();


	listener1->onMouseMove = CC_CALLBACK_1(Paul::onMouseMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this->getImg());

	listener->onTouchBegan = CC_CALLBACK_2(Paul::onTouchBegan, this);

	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->getImg());

	this->AimSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\aim\\aim3.png"));
	this->AimSprite->retain();
}

bool Paul::isWorking()
{
	return canShoot;
}

void Paul::work()
{
	if (!canShoot)
	{
		canShoot = true;
		shootReady = false;
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\Connon.png"));
		this->getImg()->setTexture(sprite->getTexture());
	}
}

void Paul::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	// fateout
	this->getImg()->removeFromParent();
	this->AimSprite->removeFromParent();
	Paul::plantSelect = false;
}

void Paul::CreateBullet()
{
	Sprite* sp = this->getImg();
	//Q弹放大
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	sp->runAction(sequence);
	//狗哥发射
	auto sp1 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\LancerBullter.png"));
	sp1->setPosition(Point(sp->getPositionX() * 1.15, sp->getPositionY()));
	sp1->setScale(0.3);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	///
	//速度获取问题
	///
	double time = (visibleSize.height + sp1->getScaleY() / 2) / 500;
	MoveTo *moveTo = MoveTo::create(time, Point(sp->getPosition().x * 1.15, visibleSize.height + sp->getPosition().y));
	addLayer(sp1);
	sp1->runAction(moveTo);

	auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\AfterLunch.png"));
	this->getImg()->setTexture(sprite->getTexture());

	PaulBullet *pb = new PaulBullet(this->touchPos, time + 1);
	setNewBirthTime();
}

void Paul::Self_Animation()
{
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(0.7f, preScale, preScale + 0.05);
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale, preScale);
	Sequence *sequence1 = Sequence::create(scaleup, scaledown, NULL);
	sp->runAction(CCRepeatForever::create(sequence1));
}

bool Paul::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	this->touchPos = touch->getLocation();
	//产生子弹
	if (canShoot && shootReady)
	{
		canShoot = false;
		shootReady = false;
		//产生子弹
		CreateBullet();
		//设置布尔值
		Paul::plantSelect = false;
		for (auto x : readyPlants)
		{
			if (x->getImg()->getTag() == Paul_tag && x->getImg()->getZOrder() <= this->getImg()->getZOrder())
			{
				Paul* p = (Paul*)x;
				p->canSelect = true;
			}
		}
		//瞄准动画
		char str[100] = { 0 };
		Vector<SpriteFrame*> allframe;
		for (int i = 1; i <= 8; i++)
		{
			sprintf(str, "Cannon\\aim\\aim%d.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(Paul::clear, this));
		Sequence *sequence = Sequence::create(Animate::create(an), Animate::create(an), actionDone, NULL);
		this->AimSprite->runAction(sequence);
		return true;
	}
	//不能选中加农炮
	if (Paul::plantSelect)
	{
		return false;
	}
	//
	Paul* p = NULL;
	for (auto x : readyPlants)
	{
		Sprite* plant = x->getImg();
		if (touchPos.x > plant->getPositionX() - plant->getContentSize().width/2 * plant->getScaleX() && touchPos.x < plant->getPositionX() + plant->getContentSize().width/2 * plant->getScaleX()
			&& touchPos.y < plant->getPositionY() + plant->getContentSize().height/2 * plant->getScaleY() && touchPos.y>plant->getPositionY() - plant->getContentSize().height/2 * plant->getScaleY()
			&& canShoot)
		{
			if (p == NULL)
			{
				p = (Paul*)x;
			}
			else if(p->getImg()->getZOrder() < plant->getZOrder())
			{
				p = (Paul*)x;
			}
		}
	}
	//
	if (p != this)
	{
		return false;
	}
	//
	if (canShoot && !shootReady)
	{
		//已经有加农炮被选中
		Paul::plantSelect = true;
		for (auto x : readyPlants)
		{
			if (x->getImg()->getTag() == Paul_tag)
			{
				Paul* p = (Paul*)x;
				p->canSelect = false;
			}
		}
		//选中效果
		Sprite* sp = this->getImg();
		CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
		CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
		Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
		sp->runAction(sequence);
		this->AimSprite->setPosition(touchPos);
		addLayer(this->AimSprite);
		shootReady = true;
		return false;
	}
	return false;
}


void Paul::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	if (canShoot && shootReady)
	{
		this->AimSprite->setPosition(Point(e->getCursorX(), e->getCursorY()));
		return;
	}
}
