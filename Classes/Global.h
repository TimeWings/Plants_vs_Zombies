#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Plants.h"
#include "TestZombie.h"
#include "Zombie.h"
#define Icing 0
USING_NS_CC;
extern std::vector <Bullet*> readyBullet;
extern std::vector <Plants*>readyPlants;
extern std::vector <Zombie*> readyZombies;
extern Map<Sprite*,Sprite*>readySun;//Ö²Îï¾«Áé£¬Ì«Ñô¾«Áé
extern std::pair<int ,std::pair<double,double>>sunCnt;
extern std::pair<double,double >BlockSize;