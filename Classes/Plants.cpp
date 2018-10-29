#include "Plants.h"
#include "EntityLayer.h"
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

void Plants::setRow(int row)
{
	_row = row;
}

int Plants::getRow()
{
	return _row;
}

void Plants::setCol(int col)
{
	_col = col;
}

int Plants::getCol()
{
	return _col;
}

void Plants::setNewBirthTime()
{
	struct timeb t1;
	ftime(&t1);
	long long seconds = t1.time * 1000 + t1.millitm;
	this->setBirthTime(seconds);
}

void Plants::addLayer(Node * entity)
{
	EntityLayer* bl = EntityLayer::getInstance();
	bl->addChild(entity, _row*2-2);
}



