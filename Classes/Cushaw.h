#pragma once
#include "Nut.h"
USING_NS_CC;
class Cushaw :public Nut
{
public:
	Cushaw(Point position, int row, int col);
	//被打之后的事件
	virtual void Attacked();

};
