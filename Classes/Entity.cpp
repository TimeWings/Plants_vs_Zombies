#include"Entity.h"
#include "Global.h"
Entity::Entity() {

}
Sprite * Entity::getImg()
{
	return _img;
}
void Entity::setImg(Sprite * img)
{
	_img = img;
}


