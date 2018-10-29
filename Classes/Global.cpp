#include "Global.h"
std::vector <Bullet*> readyBullet;
std::vector <Plants*> readyPlants;
std::vector <Zombie*> readyZombies;
Map<Sprite*, Sprite*>preSun;//Ö²Îï¾«Áé£¬Ì«Ñô¾«Áé
Map<Sprite*, Sprite*>readySun;
std::pair<int, std::pair<double, double> >sunCnt(0,std::make_pair(0,0));
std::pair<double, double >BlockSize(50,50);
int MapRow=5;