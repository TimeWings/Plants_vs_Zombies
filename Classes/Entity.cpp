#include"Entity.h"
#include "Global.h"
Entity::Entity() {

}
Entity::Entity(Sprite * img, Point position, double rotate, double scale)
{
	_img = img;
	_rotate = rotate;
	_scale = scale;
	_img->setPosition(position);
}
Sprite* Entity::getImg() {
	return _img;
}
double Entity::getRotate() {
	return _rotate;
}
double Entity::getScale() {
	return _scale;
}
void Entity::setImg(Sprite* img) {
	_img = img;
}
void Entity::setRotate(double rotate) {
	_rotate = rotate;
}
void Entity::setScale(double scale) {
	_scale = scale;
}