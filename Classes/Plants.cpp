#include "Plants.h"

Plants::Plants(Sprite * img, Point position, int hp):Entity(img,position){
	_hp = hp;
}
bool Plants::isAttacking() {
	return true;
}
int Plants::getHp() {
	return _hp;
}
void Plants::setHp(int hp) {
	_hp = hp;
}
