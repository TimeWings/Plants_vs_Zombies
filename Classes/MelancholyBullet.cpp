#include "MelancholyBullet.h"
#include "Global.h"

MelancholyBullet::MelancholyBullet()
{
}

MelancholyBullet::MelancholyBullet(Point position, int Plant_row, double angle, double distance)
{
	this->_distance = distance;
	this->_angle = angle;
	this->getRange()->push_back(Plant_row);
	this->getRange()->push_back(Plant_row-1);
	this->getRange()->push_back(Plant_row+1);
	auto sp = Sprite::create("DragBullet.png");
	sp->setTag(Penetrable_tag);
	sp->setRotation(-angle);
	//sp->setScale(0.2);
	this->setDamage(1);
	this->setSpeed(80);
	//方便以后获取子弹精灵
	this->setImg(sp);
	sp->retain();
	sp->setPosition(position);
	this->addLayer(sp);

	readyBullet.push_back(this);
	//移动函数
	this->move();
}

void MelancholyBullet::Hit_Animation(Zombie * zombie)
{
}

void MelancholyBullet::move()
{
	Point a;
	auto sp = this->getImg();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//double xie = sqrt(visibleSize.width*visibleSize.width + visibleSize.height*visibleSize.height);
	a.x = sp->getPositionX() + _distance * cos(_angle / 180 * std::_Pi);
	a.y = sp->getPositionY() + _distance * sin(_angle / 180 * std::_Pi);
	double distance = sqrt(pow((sp->getPositionX() - a.x), 2) + pow((sp->getPositionY() - a.y), 2));
	double time = distance / getSpeed();
	MoveTo *moveTo = MoveTo::create(time, a);
	//MoveTo *moveTo = MoveTo::create(time, ccp(visibleSize.width-50, sp->getPosition().y));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PeaBullet::clear, this));
	//动画序列顺序播放
	CCRotateBy* rotate = CCRotateBy::create(time, 1200);
	CCSpawn* spawn = CCSpawn::create(rotate, moveTo, NULL);
	Sequence *sequence = Sequence::create(spawn, actionDone, NULL);
	Effect();
	sp->runAction(sequence);

}
void MelancholyBullet::Effect()
{
	ParticleSystem* ps = CCParticleGalaxy::create();
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("DragEffect.png"));
	ps->setStartSize(5);
	ps->setEmissionRate(500);
	ps->setTotalParticles(200);
	ps->setPositionType(kCCPositionTypeRelative);
	ps->setPosition(0, this->getImg()->getContentSize().height / 2);
	this->getImg()->addChild(ps);
}

void MelancholyBullet::clear(Node * pSender)
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
