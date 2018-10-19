#include "Plants.h"
#include "BulletLayer.h"
#include "Global.h"
#include <time.h>
#include <sys/timeb.h>
Plants::Plants() {
	this->BirthTime = 0;
}
int Plants::getHp() {
	return _Hp;
}
void Plants::setHp(int hp) {
	_Hp = hp;
}

long long Plants::getInterval()
{
	return _WorkInterval;
}

void Plants::setInterval(long long Interval)
{
	_WorkInterval = Interval;
}

long long Plants::getBirthTime()
{
	return BirthTime;
}

void Plants::setBirthTime(long long seconds)
{
	BirthTime = seconds;
}

void Plants::getHurt(int Damage)
{
	this->_Hp -= Damage;
}

void Plants::addLayer(Node * entity)
{
	BulletLayer* bl = BulletLayer::getInstance();
	bl->addChild(entity);

}


