#include "TestZombie.h"
#include "Global.h"
TestZombie::TestZombie(Point position)
{
	CCActionManager *actionManager1;
	CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();
	// Create a new scheduler, and link it to the main scheduler
	sched1 = new CCScheduler();
	defaultScheduler->scheduleUpdateForTarget(sched1, 0, false);
	// Create a new ActionManager, and link it to the new scheudler
	actionManager1 = new CCActionManager();
	sched1->scheduleUpdateForTarget(actionManager1, 0, false);
	Sprite *sp = Sprite::create("sunFlower.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	_Speed = 10;
	_hp = 20;
	float distance = 100;
	double time = distance / _Speed;
	MoveTo *moveTo = MoveTo::create(time, ccp(0, sp->getPositionY()));
	ScaleBy * scaledown = ScaleBy::create(0.5f, 0.8f, 0.8f);
	CCSequence *sequence = CCSequence::create(moveTo, scaledown, NULL);
	sp->setActionManager(actionManager1);
	sp->runAction(sequence);
	testMap.push_back(this);
	/*CCMotionStreak* streak = CCMotionStreak::create(0.8, 10, 10, ccRED, "circle.png");
	streak->runAction(moveTo);*/
}

Sprite*TestZombie::init()
{
	return this->getImg();
}
