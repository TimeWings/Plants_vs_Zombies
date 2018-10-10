#include "Bullet.h"
Bullet::Bullet(Sprite* img, Point position, int damage, double speed):Entity(img,position) {
	_Damage = damage;
	_Speed = speed;
}
int Bullet::getDamage() {
	return true;
}
void Bullet::setDamage(int damage) {

}