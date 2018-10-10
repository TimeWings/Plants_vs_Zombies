#include"Entity.h"
Entity::Entity(Sprite * img, Point position, double rotate, double scale)
{
	_img = img;
	_position = position;
	_rotate = rotate;
	_scale = scale;
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
Point Entity::getPosition() {
	return _position;
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
void Entity::setPosition(Point position) {
	_position = position;
}