#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PotatoMine :public Plants
{
private: 
	bool bornFinish = false;
	Point position;
	int maxHp;
	int birthDelay;
public:
	PotatoMine(Point position, int row,int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	virtual void Die();
	void removeSprite(Node * pSender);
	//出生之后的自身动画
	void Self_Animation();
	//出生的动画，土豆雷特有
	void Born_Animation(Node *pSender);
	//被打之后的事件
	virtual void Attacked();
	//产生子弹
	virtual void CreateBullet();
	void afterBornHandle(Node *pSender);
	void clear(Node *pSender);
};