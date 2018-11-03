#include "LancerGun.h"
#include "Global.h"
#include "Paul.h"

LancerGun::LancerGun(Point a, int Plant_row)
{
	this->setDamage(2);
	this->getRange()->push_back(Plant_row);
	auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\Gun.png"));
	sprite->setScale(0.2);
	this->setImg(sprite);
	sprite->retain();
	sprite->setPosition(a.x + sprite->getContentSize().width*sprite->getScaleX() / 2, a.y);
	this->addLayer(sprite);
	readyBullet.push_back(this);
	this->findTarget();
	//移动函数
	this->move();
}

void LancerGun::move()
{
	if (this->targetZb != NULL)
	{
		//贝塞尔曲线
		Sprite*sp = this->getImg();
		Point TargetPoint = this->targetZb->getImg()->getPosition();
		Point targetPoint = Point(TargetPoint.x - this->targetZb->getWalkSpeed() * 2, TargetPoint.y);

		// 把角度转换为弧度
		float radian = 70 * 3.14159 / 180.0;
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
		CCRotateBy* rotate = CCRotateBy::create(2, 50);
		CCSpawn* spawn = CCSpawn::create(test, rotate, NULL);
		CallFuncN* actionDone = actionDone = CallFuncN::create(CC_CALLBACK_1(riceBullet::clear, this));
		CCSequence* sequence = CCSequence::create(spawn, actionDone, NULL);
		sp->runAction(sequence);
	}
}
