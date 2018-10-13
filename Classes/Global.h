#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Plants.h"
#include "test.h"

USING_NS_CC;

extern Map <Bullet*,Sprite*> preBullet;
extern Map <Plants*,Sprite*> prePlants;
extern Map <Bullet*, Sprite*> readyBullet;
extern Map <Plants*,Sprite*> readyPlants;
extern Map<Sprite*,Sprite*>preSun;//Ö²Îï¾«Áé£¬Ì«Ñô¾«Áé
extern Map<Sprite*,Sprite*>readySun;
extern Map<test*, Sprite*> testMap;
extern std::pair<int ,std::pair<double,double>>sunCnt;