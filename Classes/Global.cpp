#include "Global.h"
#include <iostream>
std::vector <Bullet*> readyBullet;
std::vector <Plants*> readyPlants;
std::vector <Zombie*> readyZombies;
Map<Sprite*, Sprite*>readySun;
std::vector<PlantsEnum> selectingCards;
std::vector<CardEntity*> selectingCardsEntity;
std::vector<CardEntity*> unSelectingCardsEntity;
std::vector<CardEntity*> readyCards;
Card<Shovel>* shovel;
namespace map
{
	std::pair<int, std::pair<double, double> >sunCnt(0, std::make_pair(27, 295));
	Label* sunLabel;
	std::pair<float, float >BlockSize(38.0f, 46.0f);
	std::pair<float, float >Deviation(95, 35);
	std::vector<PlantStatus*>plantstatus;
	Background* background;
    bool GameStart = false;
	int totalLevelCount = 15;
	int MapRow = 0;
	int MapCol = 0;
	void init()
	{
		while (readyBullet.size() != 0)
		{
			auto x = readyBullet.front();
			readyBullet.erase(readyBullet.begin());
			delete x;
		}
		while (readyPlants.size() != 0)
		{
			auto x = readyPlants.front();
			readyPlants.erase(readyPlants.begin());
			delete x;
		}
		while (readyZombies.size() != 0)
		{
			auto x = readyZombies.front();
			readyZombies.erase(readyZombies.begin());
			delete x;
		}
		readySun.clear();
		selectingCards.clear();
		selectingCardsEntity.clear();
		unSelectingCardsEntity.clear();
		readyCards.clear();
		sunCnt.first = 0;
		plantstatus.clear();
		GameStart = false;
	}
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
	Plants* findPlant(PlantStatus* plantstatus, const char* name)
	{
		for (Plants* x : plantstatus->plantVector)
		{
			if (strcmp(typeid(*x).name(), name) == 0)
			{
				return x;
			}
		}
		return NULL;
	}
	void RemoveRegister(const char * plant_name, int row, int col)
	{
		PlantStatus* ps = find(row, col);
		if (ps != NULL)
		{
			RemoveRegister(findPlant(ps, plant_name));
		}
		else
		{
			return;
		}
	}
	void RemoveRegister(Plants* plant)
	{
		for (int i = 0; i < plantstatus.size(); i++)
		{
			for (int j = 0; j < plantstatus.at(i)->plantVector.size(); j++)
			{
				if (plantstatus.at(i)->plantVector.at(j) == plant)
				{
					plantstatus.at(i)->plantVector.erase(plantstatus.at(i)->plantVector.begin() + j);
					std::cout << plant << "从植物列表移除成功" << std::endl;
					break;
				}
			}
		}
		plant->Die();
		std::cout << plant << "植物死亡" << std::endl;
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
		if (point.y - Deviation.second < 0)
		{
			rank.first = MapRow - (int)((point.y - Deviation.second) / BlockSize.second) + 1;
		}
		else 
		{
			rank.first = MapRow - (int)((point.y - Deviation.second) / BlockSize.second);
		}
		if (point.x - Deviation.first < 0)
		{
			rank.second = (int)((point.x - Deviation.first) / BlockSize.first) - 1;
		}
		else
		{
			rank.second = (int)((point.x - Deviation.first) / BlockSize.first) + 1;
		}
		return rank;
	}

}

