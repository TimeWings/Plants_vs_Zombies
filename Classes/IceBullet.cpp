#include "IceBullet.h"
#include "Global.h"
#include "TestZombie.h"
#include "BulletLayer.h"
#include <iostream>
#include   <windows.h>  
IceBullet::IceBullet(Point position)
{
	this->setDamage(20);
	this->setSpeed(6);
	Sprite *sp = Sprite::create("ice_Bullet.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.08);
	sp->setPosition(position.x + sp->getContentSize().width*sp->getScale() / 2, position.y);
	this->addLayer(sp);
	this->attack_Animation();
	this->move();
	readyBullet.push_back(this);
}
void IceBullet::Hit_Animation(TestZombie* zombie)
{
	////删除子弹
	Sprite*bulletSprite=this->getImg();
	bulletSprite->removeFromParent();
	streak->removeFromParent();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto x : zombie->debuff)
	{
		if (x == Icing)
		{
			std:: cout<< "此僵尸正在被冰冻" << std::endl;
			return;
		}
	}
	zombie->debuff.push_back(Icing);
	zombie->_Speed /= 2;
	zombie->sched1->setTimeScale(0.5);
	CallFuncN* actionDone= actionDone = CallFuncN::create(CC_CALLBACK_1(IceBullet::resume, this, zombie));
	CCSequence*sequence = CCSequence::create(CCDelayTime::create(0.5), actionDone,NULL);
	zombie->getImg()->runAction(sequence);
}


void IceBullet::attack_Animation()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	streak = MotionStreak::create(1, 1, 10, Color3B(152,245,255), "ice_effect2.png");
	double distance = (visibleSize.width  - this->getImg()->getPositionX())/15;
	double time = distance / getSpeed();
	streak->setPosition(this->getImg()->getPosition());
	Point a = ccp(visibleSize.width , this->getImg()->getPosition().y);
	auto moveto = MoveTo::create(time, a);
	auto fun = [this](Node*psender)
	{
		auto streak = static_cast<MotionStreak*>(psender);
		streak->removeFromParent();
	};
	auto call = CallFuncN::create(fun);
	streak->runAction(Sequence::create(moveto, call, NULL));
	//addLayer(streak);

	ParticleSystem* ps = ParticleMeteor::create();
	//因为偷懒，我直接用helloWorld里的close 图片当雪花  
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("ice_effect3.png"));
	//ps->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	//ps->setStartSize(50);
	//ps->setDuration(-1);
	//ps->setEmissionRate(10);
	//ps->setStartRadius(10);
	//ps->setAutoRemoveOnFinish(true);
	//ps->setPositionType(kCCPositionTypeRelative);
	//ps->setColor(Color4F(152, 245, 255,0));
	ps->setPosition(this->getImg()->getPosition());//生成的雪花从这个坐标往下落  
	this->getImg()->addChild(ps,0);
	//addLayer(ps);
}

void IceBullet::resume(Node *pSender, TestZombie* zombie)
{
	std::cout << "cnm" << std::endl;
	for (int i = 0; i < zombie->debuff.size(); i++)
	{
		if (zombie->debuff.at(i) == Icing)
		{
			zombie->debuff.erase(zombie->debuff.begin() + i);
			std::cout << "恢复！！！" << std::endl;;
			break;
		}
	}
	zombie->_Speed *= 2;
	zombie->sched1->setTimeScale(1);
}

