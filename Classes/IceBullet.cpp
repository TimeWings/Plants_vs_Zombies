#include "IceBullet.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>
IceBullet::IceBullet(Point position,int Plant_row)
{
	this->getRange()->push_back(Plant_row);
	this->setDamage(1);
	this->setSpeed(6);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("ice_Bullet.png"));
	this->setImg(sp);
	sp->setTag(En_Burn);
	sp->retain();
	sp->setScale(0.08);
	sp->setPosition(position.x + sp->getContentSize().width*sp->getScale() / 2, position.y);
	this->addLayer(sp);
	this->move();
	this->attack_Animation();
	readyBullet.push_back(this);
}
void IceBullet::Hit_Animation(Zombie* zombie)
{
	////删除子弹
	Sprite*bulletSprite=this->getImg();
	bulletSprite->removeAllChildrenWithCleanup(true);
	bulletSprite->removeFromParent();
	//streak->removeFromParent();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
	ParticleSystem* ps = CCParticleGalaxy::create();
	ps->setPosition(zombie->getImg()->getPosition());
	ps->setLife(1);
	ps->setDuration(0.5);
	addLayer(ps);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto x : *(zombie->getDebuff()))
	{
		if (x == Icing)
		{
			std:: cout<< "此僵尸正在被冰冻" << std::endl;
			return;
		}
	}
	zombie->getDebuff()->push_back(Icing);
	zombie->getScheduler()->setTimeScale(0.25);
	CallFuncN* actionDone= actionDone = CallFuncN::create(CC_CALLBACK_1(IceBullet::resume, this, zombie));
	CCSequence*sequence = CCSequence::create(CCDelayTime::create(5), actionDone,NULL);
	zombie->getImg()->runAction(sequence);
}


void IceBullet::attack_Animation()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//streak = MotionStreak::create(2, 1, 10, Color3B(255,255,255), "ice_effect.png");
	//double distance = (visibleSize.width  - this->getImg()->getPositionX())/15;
	//double time = distance / getSpeed();
	/*streak->setPosition(this->getImg()->getPosition());
	this->streak = streak;
	Point a = ccp(visibleSize.width , this->getImg()->getPosition().y);
	auto moveto = MoveTo::create(time, a);
	auto fun = [this](Node*psender)
	{
		auto streak = static_cast<MotionStreak*>(psender);
		streak->removeFromParent();
	};
	auto call = CallFuncN::create(fun);
	CCActionInterval *colorAction =(CCActionInterval *)CCSequence::create(
		CCTintTo::create(0.2f, 255, 0, 0),
		CCTintTo::create(0.2f, 0, 255, 0),
		CCTintTo::create(0.2f, 0, 0, 255),
		CCTintTo::create(0.2f, 0, 255, 255),
		CCTintTo::create(0.2f, 255, 255, 0),
		CCTintTo::create(0.2f, 255, 0, 255),
		CCTintTo::create(0.2f, 255, 255, 255),
		NULL);
	Spawn* spawn = Spawn::create(moveto, colorAction,NULL);
	streak->runAction(Sequence::create(spawn, call, NULL));
	addLayer(streak);*/
	Sprite*sp = this->getImg();
	ParticleSystem* ps = ParticleMeteor::create();
	//因为偷懒，我直接用helloWorld里的close 图片当雪花  
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("ice_effect3.png"));
	//ps->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	ps->setStartSize(40);
	//ps->setLife(1);
	//ps->setDuration(-1);
	//ps->setEmissionRate(200);
	//ps->setStartRadius(10);
	//ps->setAutoRemoveOnFinish(true);
	ps->setPositionType(kCCPositionTypeRelative);
	//ps->setColor(Color4F(152, 245, 255,0));
	ps->setPosition(sp->getContentSize().width/2,sp->getContentSize().height/2);
	this->getImg()->addChild(ps);
}

void IceBullet::resume(Node *pSender, Zombie* zombie)
{
	std::cout << "cnm" << std::endl;
	for (int i = 0; i < zombie->getDebuff()->size(); i++)
	{
		if (zombie->getDebuff()->at(i) == Icing)
		{
			zombie->getDebuff()->erase(zombie->getDebuff()->begin() + i);
			std::cout << "恢复！！！" << std::endl;;
			break;
		}
	}
	zombie->getScheduler()->setTimeScale(1);
}

