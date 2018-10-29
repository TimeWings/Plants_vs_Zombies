#include "Zombie.h"
#include "EntityLayer.h"
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

int Zombie::getRow()
{
	return _row;
}

void Zombie::setRow(int row)
{
	_row = row;
	if(this->getImg() != NULL)
		this->getImg()->setZOrder(_row * 2 - 1);
}
void Zombie::setCol(int col)
{
	_col = col;
}
int Zombie::getCol()
{
	return _col;
}
double Zombie::getInterval()
{
	return _BiteInterval;
}

void Zombie::setInterval(double BiteInterval)
{
	_BiteInterval = BiteInterval;
}

void Zombie::setWalkSpeed(double WalkSpeed)
{
	_WalkSpeed=WalkSpeed;
}

double Zombie::getWalkSpeed()
{
	if (isMeeting())
	{
		return 0;
	}
	else
	{
		return _WalkSpeed * sched->getTimeScale();
	}
}

double Zombie::getPreWalkSpeed()
{
	return _WalkSpeed;
}

bool Zombie::hasHead()
{
	return _Head;
}

void Zombie::setHead(bool Head)
{
	_Head = Head;
}

bool Zombie::isMeeting()
{
	return _meeting;
}

void Zombie::setMeeting(bool meeting)
{
	_meeting = meeting;
}


std::vector<int>* Zombie::getDebuff() 
{
	return &debuff;
}

void Zombie::addLayer(Node * entity)
{
	EntityLayer* zl = EntityLayer::getInstance();
	zl->addChild(entity, _row*2-1);
}

void Zombie::setSche(Node* sprite)
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

CCScheduler * Zombie::getScheduler()
{
	return sched;
}
