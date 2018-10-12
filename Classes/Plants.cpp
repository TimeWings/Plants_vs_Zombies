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

long long Plants::getInterval()
{
	return _BulletInterval;
}

void Plants::setInterval(long long Interval)
{
	_BulletInterval = Interval;
}

long long Plants::getBirthTime()
{
	return BirthTime;
}

void Plants::setBirthTime(long long seconds)
{
	BirthTime = seconds;
}
