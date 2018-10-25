#pragma once
#include "Nut.h"
USING_NS_CC;
class NutPlus :public Nut
{
public:
	NutPlus(Point position, int row);
	NutPlus();

	void Attacked();

};
