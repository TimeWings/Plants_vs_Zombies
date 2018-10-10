#include "Plants.h"

Plants::Plants(Sprite * img, Point position, int hp, double Interval):Entity(img,position){
	_Hp = hp;
	_BulletInterval = Interval;
}
bool Plants::isAttacking() {
	return true;
}
int Plants::getHp() {
	return _Hp;
}
void Plants::setHp(int hp) {
	_Hp = hp;
}

double Plants::getInterval()
{
	return 0.0;
}

void Plants::setInterval(double Interval)
{
}
