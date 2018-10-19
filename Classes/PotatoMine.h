#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PotatoMine :public Plants
{
private: 
	bool bornFinish = false;
public:
	PotatoMine(Point position);
	virtual bool isWorking();//是否能工作
	virtual void work();
	virtual void Die();
	//出生之后的自身动画
	void Self_Animation();
	//出生的动画，土豆雷特有
	void Born_Animation(Node *pSender, Point position);
	//被打之后的事件
	virtual void Attacked();
	//产生子弹
	virtual void CreateBullet();
	void afterBornHandle(Node *pSender, Point position);
	void clear(Node *pSender);
};