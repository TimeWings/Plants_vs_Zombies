#include"Entity.h"
#include "Global.h"
Entity::Entity() {

}
Entity::Entity(Point position, double rotate)
{
	_rotate = rotate;
}
Sprite * Entity::getImg()
{
	return _img;
}
void Entity::setImg(Sprite * img)
{
	_img = img;
}
double Entity::getRotate() {
	return _rotate;
}
void Entity::setRotate(double rotate) {
	_rotate = rotate;
}
