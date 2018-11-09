#include "PlantStatus.h"
#include "EntityLayer.h"
#include <iostream>
#include "Global.h"
USING_NS_CC;
using namespace std;
using namespace map;

PlantStatus::PlantStatus(int row,int col,int BlockType,bool enable)
{
	_row = row;
	_col = col;
	_BlockType = BlockType;
	Enabled = enable;
}


PlantStatus::~PlantStatus()
{
}


