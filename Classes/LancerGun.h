#pragma once
#include "cocos2d.h"
#include "riceBullet.h"
#include <iostream>

class LancerGun :public riceBullet
{
public:
	LancerGun(Point a, int Plant_row);
	void move();
};