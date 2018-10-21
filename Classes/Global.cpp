#include "Global.h"
std::vector <Bullet*> readyBullet;
std::vector <Plants*> readyPlants;
std::vector <Zombie*> readyZombies;
Map<Sprite*, Sprite*>preSun;//Ö²Îï¾«Áé£¬Ì«Ñô¾«Áé
Map<Sprite*, Sprite*>readySun;
std::vector<TestZombie*> testMap;
std::pair<int, std::pair<double, double> >sunCnt(0,std::make_pair(0,0));