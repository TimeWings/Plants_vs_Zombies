#include "IceBullet.h"
#include "Global.h"
#include "TestZombie.h"
#include <iostream>
IceBullet::IceBullet(Point position)
{
	Sprite *sp = Sprite::create("sword1.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.15);
	sp->setPosition(position.x + sp->getContentSize().width*sp->getScale() / 2, position.y);
	preBullet.push_back(this);
}

void IceBullet::work()
{
	Self_Animation();
}

void IceBullet::Hit_Animation(TestZombie* zombie)
{
	////É¾³ý×Óµ¯
	Sprite*bulletSprite=this->getImg();
	bulletSprite->removeFromParent();
	
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
			std:: cout<< "´Ë½©Ê¬ÕýÔÚ±»±ù¶³" << std::endl;
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

Sprite * IceBullet::attack_Animation()
{
	/*Sprite * ice = sprite::create("icehit.png");
	ice->setscale(0.3);
	Point a = ccp(sp->getpositionx() - sp->getcontentsize().width / 2 * sp->getscale(), sp->getpositiony());
	ice->setposition(a);
	CCfollow * follow = ccfollow::create(sp,ccrectmake(0, 0, 600, 600));
	ice-> runaction(follow);
	return ice;*/
	return NULL;
}

void IceBullet::Self_Animation()
{
	//ActionInterval * rotateto = RotateBy::create(0.5, 180);
    //sp->runAction(RepeatForever::create(rotateto));
}

void IceBullet::resume(Node *pSender, TestZombie* zombie)
{
	std::cout << "cnm" << std::endl;
	for (int i = 0; i < zombie->debuff.size(); i++)
	{
		if (zombie->debuff.at(i) == Icing)
		{
			zombie->debuff.erase(zombie->debuff.begin() + i);
			std::cout << "»Ö¸´£¡£¡£¡" << std::endl;;
			break;
		}
	}
	zombie->_Speed *= 2;
	zombie->sched1->setTimeScale(1);
}

