#include "Zombie.h"
#include "EntityLayer.h"
#include "Global.h"
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
		this->getImg()->setZOrder(_row * 3 - 1);
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
	zl->addChild(entity, _row * 3 - 1);
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
	if (hasEquip()) {
		getEquip()->getImg()->setActionManager(actionManager);
	}
}

void Zombie::setEquip(ZombieEquipment * equip)
{
	this->equip = equip;
}

ZombieEquipment * Zombie::getEquip()
{
	return equip;
}

bool Zombie::hasEquip()
{
	return equip != nullptr;
}

CCScheduler * Zombie::getScheduler()
{
	return sched;
}

void Zombie::DamagePlant(Node * pSender, PlantStatus *plantstatus)
{

	if (plantstatus->plantVector.size() == 0 || strcmp(typeid(*(plantstatus->plantVector.at(0))).name(), "class Lucker") == 0) {
		this->Move();
		this->setMeeting(false);
		return;
	}
	plantstatus->plantVector.at(0)->getHurt(1);
	plantstatus->plantVector.at(0)->Attacked();
}

void Zombie::clear(Node * pSender)
{
	pSender->removeFromParent();
	pSender->removeAllChildrenWithCleanup(true);
}

void Zombie::clear_from_vector(Node * pSender)
{
	for (unsigned i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i) == this)
		{
			readyZombies.erase(readyZombies.begin() + i);
			break;
		}
	}
}