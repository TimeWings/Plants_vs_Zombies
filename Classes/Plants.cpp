#include "Plants.h"
#include <time.h>
#include <sys/timeb.h>
Plants::Plants() {

}
int Plants::getHp() {
	return _Hp;
}
void Plants::setHp(int hp) {
	_Hp = hp;
}

double Plants::getInterval()
{
	return _BulletInterval;
}

void Plants::setInterval(double Interval)
{
	_BulletInterval = Interval;
}

int Plants::getBirthTime()
{
	return BirthTime;
}

void Plants::setBirthTime(int seconds)
{
	BirthTime = seconds;
}
