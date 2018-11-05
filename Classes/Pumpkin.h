#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "Zombie.h"
USING_NS_CC;
class Pumpkin :public Plants
{
private:
	Point position;
	float attackRange;
	float jumpDuration;
	bool isChecking;
	bool isJumping;
public:
	Pumpkin(Point position, int row,int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	void CheckZombies();
	void JumpTo(Zombie * zombie);
	void press(Node * pSender, Zombie * zombie);
	virtual void Die();
	//特有的自身动画
	void Self_Animation();
	//被打之后的事件
	virtual void Attacked();
	void clearZombie(Node * pSender, Zombie * zombie);
	void clear(Node * pSender);
};