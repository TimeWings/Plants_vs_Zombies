#include "IceBullet.h"
#include "Global.h"
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

void IceBullet::Hit_Animation(Sprite * sp, std::vector<int>debuff1, Vector<Action*>action)
{
	////É¾³ý×Óµ¯
	//Sprite*bulletSprite=this->getImg();
	//bulletSprite->removeFromParent();
	//
	//for (int i = 0; i < readyBullet.size(); i++)
	//{
	//	if (readyBullet.at(i) == this)
	//	{
	//		readyBullet.erase(readyBullet.begin() + i);
	//		break;
	//	}
	//}
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	//for (auto x : debuff)
	//{
	//	if (x == Icing)
	//	{
	//		std:: cout<< "´Ë½©Ê¬ÕýÔÚ±»±ù¶³" << std::endl;
	//		return;
	//	}
	//}
	//debuff.push_back(Icing);
	//Action  * action = sp->getActionByTag(tag);
	//sp->stopAction(action);
	//speed_ /= 2;
	//std::vector<int>a;
	//std::cout << speed_ << std::endl;
	//float distance = sp->getPositionX();
	//double time = distance / speed_;
	//MoveTo *moveTo = MoveTo::create(time, ccp(0, sp->getPositionY()));
	//auto actionDone = CallFuncN::create(CC_CALLBACK_1(IceBullet::resume, this,moveTo,debuff1));
	//Sequence *sequence = Sequence::create(moveTo, CCDelayTime::create(0.5),actionDone,NULL);
	//sp->runAction(sequence);
}

Sprite * IceBullet::attack_Animation()
{
	//Sprite * ice = Sprite::create("iceHit.png");
	//ice->setScale(0.3);
	//Point a = ccp(sp->getPositionX() - sp->getContentSize().width / 2 * sp->getScale(), sp->getPositionY());
	//ice->setPosition(a);
	////CCFollow * follow = CCFollow::create(sp,CCRectMake(0, 0, 600, 600));
	////ice-> runAction(follow);
	//return ice;
	return NULL;
}

void IceBullet::Self_Animation()
{
	//ActionInterval * rotateto = RotateBy::create(0.5, 180);
    //sp->runAction(RepeatForever::create(rotateto));
}

void IceBullet::resume(Node *pSender, Action *action, std::vector<int>debuff)
{
	std::cout << "cnm" << std::endl;
	for (int i = 0; i < debuff.size(); i++)
	{
		if (debuff.at(i) == Icing)
		{
			debuff.erase(debuff.begin() + i);
			std::cout << "»Ö¸´£¡£¡£¡" << std::endl;;
			break;
		}
	}
	pSender->stopAction(action);
	speed_ *= 2;
	float distance = pSender->getPositionX();
	double time = distance / speed_;
	MoveTo *moveTo = MoveTo::create(time, ccp(0, pSender->getPositionY()));
}
