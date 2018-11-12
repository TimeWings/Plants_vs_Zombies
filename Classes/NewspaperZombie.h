#pragma once
#include "DoorZombie.h"

class NewspaperZombie : public DoorZombie
{
public:
	NewspaperZombie();
	NewspaperZombie(Point position, int row, int col);
	virtual void Attack(PlantStatus *plantstatus);
	void Attack_with_Equip(PlantStatus *plantstatus);
	void BasicAttack(PlantStatus *plantstatus);
	virtual void Move();
	void Move_with_Equip();
	void BasicMove();
	void AfterLostEquip(Node * pSender);
	virtual Sprite *MagnetEquip();
	virtual void Lost_Equip();
	virtual void LostHead();
};