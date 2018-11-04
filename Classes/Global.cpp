#include "Global.h"
std::vector <Bullet*> readyBullet;
std::vector <Plants*> readyPlants;
std::vector <Zombie*> readyZombies;
Map<Sprite*, Sprite*>readySun;
std::vector<Plantable*> plantableList;
namespace map
{
	std::pair<int, std::pair<double, double> >sunCnt(0, std::make_pair(0, 0));
	std::pair<float, float >BlockSize(35.0f, 52.0f);
	int MapRow = 5;
	int MapCol = 9;
	int BlockStatus[50][50] = { 0 };

	Point Rank2Point(int row, int col)
	{
		Point a;
		a.x = BlockSize.first + (col-1) * BlockSize.first;
		a.y = BlockSize.second + fabs(row - MapRow)*BlockSize.second;
		return a;
	}
	std::pair<int, int> Point2Rank(Point point)
	{
		std::pair<int, int>rank;
		rank.first = MapRow - (int)((point.y- 0.5*BlockSize.second) / BlockSize.second) ;
		rank.second = (int)((point.x- 0.5*BlockSize.first)/ BlockSize.first) + 1;
		return rank;
	}

}

