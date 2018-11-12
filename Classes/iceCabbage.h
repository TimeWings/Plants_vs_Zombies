#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include "JannuDaruku.h"
USING_NS_CC;
class iceCabbage : public JannuDaruku
{
private:
	Action* drivingOut;
public:
	iceCabbage(Point position, int row, int col);
	virtual void thisDie();
	void creatSprite();
	bool judgeIsDriving(Zombie * zombie);
	void Effect(Node *pSender);
	void clearIceSprite(Node * pSender, Sprite * iceSprite, Zombie* zombie);
	void zombieRun(Node * pSender, Zombie* zombie);
};