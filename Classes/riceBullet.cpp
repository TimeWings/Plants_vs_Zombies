#include "riceBullet.h"
#include "Global.h"
#include "Zombie.h"


riceBullet::riceBullet()
{
}

riceBullet::riceBullet(Point a, int Plant_row)
{
	this->setDamage(2);
	this->getRange()->push_back(Plant_row);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("riceShooter\\rice.png"));
	sp->setScale(0.5);
	this->getImg()->setTag(Pitcher_tag);
	this->setImg(sp);
	sp->retain();
	sp->setPosition(a.x + sp->getContentSize().width*sp->getScaleX() / 2, a.y);
	this->addLayer(sp);
	readyBullet.push_back(this);
	this->findTarget();
	//移动函数
	this->move();
}

void riceBullet::clear(Node * pSender)
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

void riceBullet::findTarget()
{
	double minDistance = 100000000;
	Zombie* zombie = NULL;
	for (int i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i)->getRow() != this->getRange()->front())
		{
			continue;
		}
		Sprite *sp = readyZombies.at(i)->getImg();
		double x1 = this->getImg()->getPositionX();
		double x2 = sp->getPositionX();
		double y1 = this->getImg()->getPositionY();
		double y2 = sp->getPositionY();
		double dis = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
		if (dis < minDistance)
		{

			minDistance = dis;
			zombie = readyZombies.at(i);
		}
	}
	this->targetZb = zombie;
}

void riceBullet::move()
{
	if (this->targetZb != NULL)
	{
		//贝塞尔曲线
		Sprite*sp = this->getImg();
		Point TargetPoint = this->targetZb->getImg()->getPosition();
		Point targetPoint = Point(TargetPoint.x - this->targetZb->getWalkSpeed() * 2, TargetPoint.y);

		// 把角度转换为弧度
		float radian = 60 * 3.14159 / 180.0;
		// 第一个控制点为抛物线左半弧的中点
		float q1x = sp->getPosition().x + (targetPoint.x - sp->getPosition().x) / 4.0;
		CCPoint q1 = ccp(q1x, 0 + targetPoint.y + cos(radian)*q1x);
		// 第二个控制点为整个抛物线的中点
		float q2x = sp->getPosition().x + (targetPoint.x - sp->getPosition().x) / 2.0;
		CCPoint q2 = ccp(q2x, 0 + sp->getPosition().y + cos(radian)*q2x);

		ccBezierConfig cfg;
		cfg.controlPoint_1 = q1;
		cfg.controlPoint_2 = q2;
		cfg.endPosition = targetPoint;
		//使用CCEaseInOut让曲线运动有一个由慢到快的变化，显得更自然
		CCEaseInOut* test = CCEaseInOut::create(CCBezierTo::create(2, cfg), 0.5);
		CCRotateBy* rotate = CCRotateBy::create(2, 1200);
		CCSpawn* spawn = CCSpawn::create(test, rotate, NULL);
		CallFuncN* actionDone = actionDone = CallFuncN::create(CC_CALLBACK_1(riceBullet::clear, this));
		CCSequence* sequence = CCSequence::create(spawn, actionDone, NULL);
		sp->runAction(sequence);
	}
}

void riceBullet::attack_Animation()
{
}

void riceBullet::Hit_Animation(Zombie * zombie)
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
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(riceBullet::clearNode, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

