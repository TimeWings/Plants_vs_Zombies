#include "ZombieEquipment.h"
#include "Zombie.h"

int ZombieEquipment::getHp()
{
	return _Hp;
}

void ZombieEquipment::setHp(int Hp)
{
	_Hp = Hp;
}

bool ZombieEquipment::isMetal()
{
	return _Metal;
}

void ZombieEquipment::setMetal(bool Metal)
{
	_Metal = Metal;
}

void ZombieEquipment::addLayer(Node * entity, Zombie *zombie)
{
	zombie->getImg()->addChild(entity);
}
