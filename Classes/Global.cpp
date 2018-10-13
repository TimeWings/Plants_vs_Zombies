#include "Global.h"
Map <Bullet*, Sprite*> preBullet;
Map <Plants*, Sprite*> prePlants;
Map <Bullet*, Sprite*> readyBullet;
Map <Plants*, Sprite*> readyPlants;
Map<Sprite*, Sprite*>preSun;
Map<Sprite*, Sprite*>readySun;
Map<test*, Sprite*> testMap;
std::pair<int, std::pair<double, double> >sunCnt(0,std::make_pair(0,0));