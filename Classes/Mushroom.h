#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "Bullet.h"
#include "PeaShooter.h"
#include "MushroomBullet.h"
USING_NS_CC;

class Mushroom : public PeaShooter
{
private:
	bool haveBullet;
	float Scale;
public:
	Mushroom(Point position, int row,int col);
	void CreateBullet();
	void Self_Animation();
	void clear(Node *pSender);
	void clearBullet(Node *pSender, MushroomBullet *bp);
	void Die();
};