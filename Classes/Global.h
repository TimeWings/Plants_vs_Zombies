#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Plants.h"
#include "test.h"
#include <vector>

USING_NS_CC;

extern Map <Bullet*,Sprite*> preBullet;
extern Map <Plants*,Sprite*> prePlants;
extern Map <Bullet*, Sprite*> readyBullet;
extern Map <Plants*,Sprite*> readyPlants;
extern Map<test*, Sprite*> testMap;