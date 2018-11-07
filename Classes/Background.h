#pragma once
#include "Entity.h"
class Background :
	public Entity
{
public:
	static int type;//0代表全陆地地图，1代表水路地图,2代表黑夜全陆地
	static Node* holesStencil;
public:
	Background();
	void initPlantStatus();
};

