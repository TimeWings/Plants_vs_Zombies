#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Plants.h"
#include "Zombie.h"
#define Icing 0
USING_NS_CC;
extern std::vector <Bullet*> readyBullet;
extern std::vector <Plants*>readyPlants;
extern std::vector <Zombie*> readyZombies;
extern Map<Sprite*,Sprite*>readySun;//Ö²Îï¾«Áé£¬Ì«Ñô¾«Áé

namespace map 
{
	extern std::pair<int, std::pair<double, double>>sunCnt;
	extern std::pair<double, double >BlockSize;
	extern int MapRow;
	extern int MapCol;
	extern int BlockStatus[50][50];
	Point Rank2Point(int row, int col);
	extern std::pair<int, int>Point2Rank(Point point);
}

