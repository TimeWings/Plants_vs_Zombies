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

bool Zombie::hasHand()
{
	return _Hand;
}

void Zombie::setHand(bool Hand)
{
	_Hand = Hand;
}

std::vector<int> Zombie::getDebuff() 
{
	return debuff;
}