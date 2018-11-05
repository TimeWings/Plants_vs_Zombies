#include "Global.h"
#include <iostream>
std::vector <Bullet*> readyBullet;
std::vector <Plants*> readyPlants;
std::vector <Zombie*> readyZombies;
Map<Sprite*, Sprite*>readySun;
namespace map
{
	std::pair<int, std::pair<double, double> >sunCnt(0, std::make_pair(0, 0));
	std::pair<float, float >BlockSize(38.0f, 46.0f);
	std::pair<float, float >Deviation(95, 35);
	std::vector<PlantStatus*>plantstatus;
	int MapRow = 5;
	int MapCol = 9;
	int BlockStatus[50][50] = { 0 };
	PlantStatus* find(int row, int col)
	{
		for (PlantStatus* x : plantstatus)
		{
			if (x->_row == row && x->_col == col)
			{
				return x;
			}
		}
		return NULL;
	}
	void RemoveRegister(Plants* plant, int row, int col)
	{
		PlantStatus* ps = find(row, col);
		if (ps != NULL)
		{
			for (int i = 0; i < ps->plantVector.size(); i++)
			{
				if (ps->plantVector.at(i) == plant)
				{
					ps->plantVector.erase(ps->plantVector.begin() + i);
					std::cout << plant << "从植物列表移除成功" << std::endl;
					break;
				}
			}
		}
		else
		{
			return;
		}
	}
	Point Rank2Point(int row, int col)
	{
		Point a;
		a.x = Deviation.first + (col-1) * BlockSize.first+0.5*BlockSize.first;
		a.y = Deviation.second + fabs(row - MapRow)*BlockSize.second+0.5*BlockSize.second;
		return a;
	}
	std::pair<int, int> Point2Rank(Point point)
	{
		std::pair<int, int>rank;
		rank.first = MapRow - (int)((point.y- Deviation.second) / BlockSize.second) ;
		rank.second = (int)((point.x- Deviation.first)/ BlockSize.first) + 1;
		return rank;
	}

}

