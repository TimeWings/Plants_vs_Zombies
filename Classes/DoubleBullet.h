#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"
#include "PeaBullet.h"
USING_NS_CC;
class DoubleBullet : public PeaBullet
{
public:
	DoubleBullet(Point position);
}; 
