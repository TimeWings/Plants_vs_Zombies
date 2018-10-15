#include "Bullet.h"
Bullet::Bullet()
{

}
Bullet::Bullet(Point position, int damage, double speed):Entity(position) {
	_Damage = damage;
	_Speed = speed;
}
int Bullet::getDamage() {
	return true;
}
void Bullet::setDamage(int damage) {
	_Damage = damage;
}

double Bullet::getSpeed()
{
	return _Speed;
}

void Bullet::setSpeed(double speed)
{
	_Speed = speed;
}
