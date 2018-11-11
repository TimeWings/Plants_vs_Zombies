#pragma once
#include "Door.h"

class Newspaper : public Door 
{
public:
	Newspaper();
	virtual void Move();
	void NewspaperMove();
	virtual void Attack(double interval);
	void NewspaperAttack(double interval);
};