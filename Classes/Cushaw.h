#pragma once
#include "Nut.h"
USING_NS_CC;
class Cushaw :public Nut
{
private:
	bool isProtecting = false;;
public:
	Cushaw(Point position, int row, int col);
	void work();
	//被打之后的事件
	virtual void Attacked();

};
