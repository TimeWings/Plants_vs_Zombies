#include "Zombie.h"

Zombie::Zombie()
{
}

int Zombie::getHp()
{
	return _Hp;
}

void Zombie::setHp(int hp)
{
	_Hp = hp;
}

long long Zombie::getInterval()
{
	return _BiteInterval;
}

void Zombie::setInterval(long long BiteInterval)
{
	_BiteInterval = BiteInterval;
}

long long Zombie::getBirthTime()
{
	return BirthTime;
}

void Zombie::setBirthTime(long long seconds)
{
	BirthTime = seconds;
}

int Zombie::getWalkSpeed()
{
	return _WalkSpeed;
}

void Zombie::setWalkSpeed(int WalkSpeed)
{
	_WalkSpeed = WalkSpeed;
}

bool Zombie::hasHead()
{
	return _Head;
}

void Zombie::setHead(bool Head)
{
	_Head = Head;
}

std::vector<int> Zombie::getDebuff() 
{
	return debuff;
}

void Zombie::addLayer(Node * entity)
{
	ZombieLayer* zl = ZombieLayer::getInstance();
	zl->addChild(entity);
}

void Zombie::setActionManger(Node* sprite)
{
	CCActionManager *actionManager;
	CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();
	// Create a new scheduler, and link it to the main scheduler
	sched = new CCScheduler();
	defaultScheduler->scheduleUpdateForTarget(sched, 0, false);
	// Create a new ActionManager, and link it to the new scheudler
	actionManager = new CCActionManager();
	sched->scheduleUpdateForTarget(actionManager, 0, false);
	sprite->setActionManager(actionManager);
}
