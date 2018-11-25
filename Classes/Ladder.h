#pragma once
#include "Nut.h"
USING_NS_CC;
class Ladder :public Nut
{
public:
	Ladder(Point position, int row, int col);
	virtual void Die();
	void clear(Node* pSender);
};
