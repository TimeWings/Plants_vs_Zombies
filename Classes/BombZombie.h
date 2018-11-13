#pragma once
#include "BasicZombie.h"
#include "Plants.h"
#include "PlantStatus.h"


class BombZombie : public BasicZombie
{
private:
	bool isOpening=false;
public:
	BombZombie(Point position, int row, int col);
	bool isWorking();
	void work();
	void BoxOpen();
	void Bomb(Node* pSender);
	void Bomb_damage();
	virtual void Die(Node * pSender);
	virtual void LostHead();
	virtual void BasicMove();
	virtual void BasicAttack(PlantStatus *plantstatus);
};
