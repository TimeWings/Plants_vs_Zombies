#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class JannuDaruku : public Plants
{
protected:
	Point position;
	bool thisIsEnd;
public:
	JannuDaruku();
	JannuDaruku(Point position,int row,int col);
	virtual bool isWorking();//是否能工作
    void work();
	void Die();
	virtual void thisDie();
	void Effect(Node * pSender);
	void zombiesDie();
	void creatSprite();
	//产生子弹
	virtual void CreateBullet();
	//清理精灵
	void clear(Node * pSender);
};