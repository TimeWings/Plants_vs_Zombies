#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Plants.h"
#include "test.h"
#include "TestZombie.h"
#define Icing 0
USING_NS_CC;

extern std::vector <Bullet*> preBullet;
extern std::vector <Plants*> prePlants;
extern std::vector <Bullet*> readyBullet;
extern std::vector <Plants*> readyPlants;
extern Map<Sprite*,Sprite*>preSun;//Ö²Îï¾«Áé£¬Ì«Ñô¾«Áé
extern Map<Sprite*,Sprite*>readySun;
extern std::vector<TestZombie*> testMap;
extern std::pair<int ,std::pair<double,double>>sunCnt;