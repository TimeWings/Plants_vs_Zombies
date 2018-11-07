#pragma once
#include "Entity.h"
class Background :
	public Entity
{
private:
	int type = 1;//0代表全陆地地图，1代表水路地图
public:
	Background();
	void initPlantStatus();
};

