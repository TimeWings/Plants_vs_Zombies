#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class Sunflower :public Plants
{
public:
	Sunflower(Point position,int row,int col);
	void work();
	void Attacked();
	void Self_Animation();
	void CreateSun();
	bool isWorking();//是否能工作
	void clearSun(Node * pSender, Sprite * sunFlower);
	void clear(Node * pSender);

};