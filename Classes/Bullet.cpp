#include "Bullet.h"
#include "Global.h"
#include "BulletLayer.h"
Bullet::Bullet()
{

}
Bullet::Bullet(Point position, int damage, double speed) {
	_Damage = damage;
	_Speed = speed;
}
int Bullet::getDamage() {
	return _Damage;
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



void Bullet::cal_damage(TestZombie * zombie)
{
	zombie->_hp -= this->getDamage();
}

void Bullet::addLayer(Node * entity)
{
	BulletLayer* bl = BulletLayer::getInstance();
	bl->addChild(entity);
}

