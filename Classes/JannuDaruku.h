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
	virtual void thisDie();
	void Effect(Node * pSender);
	virtual void zombiesDie();
	virtual void creatSprite();
	void clearNode(Node * pSender);
	// 通过 Plants 继承
	virtual void Attacked() override;
};