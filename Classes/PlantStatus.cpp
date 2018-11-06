#include "PlantStatus.h"
#include "EntityLayer.h"
#include <iostream>
#include "Global.h"
USING_NS_CC;
using namespace std;
using namespace map;
//vector<Plantable*> plantableList;

PlantStatus::PlantStatus(int row,int col,int BlockType)
{
	_row = row;
	_col = col;
	_BlockType = BlockType;
}


PlantStatus::~PlantStatus()
{
}


