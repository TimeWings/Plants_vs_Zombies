#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Plants.h"
#include <vector>
USING_NS_CC;

extern std::vector <Bullet*> preBullet;
extern std::vector <Plants*> prePlants;
extern std::vector <Bullet*> readyBullet;
extern std::vector <Plants*> readyPlants;