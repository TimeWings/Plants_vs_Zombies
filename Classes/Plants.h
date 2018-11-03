#pragma once
#include "cocos2d.h"
#include "Entity.h"
#define Penetrable_tag 159159//穿透tag
#define Pitcher_tag 158158//投手tag
#define Paul_tag 158157//投手tag

USING_NS_CC;
class Plants:public Entity
{
private:
	int _Hp; //血量
	long long BirthTime; //诞生时间
	long long _WorkInterval; //工作间隔
	int _row;
	int _col;
public:
	Plants(); //构造函数
	int getHp(); 
	void setHp(int hp);
	long long getInterval(); 
	void setInterval(long long Interval);
	long long getBirthTime();
	void setBirthTime(long long seconds);
	void getHurt(int Damage);
	void setRow(int row);
	int getRow();
	void setCol(int col);
	int getCol();
	void setNewBirthTime();
	//把精灵直接放到图层上
	void addLayer(Node* entity);
	virtual void work() = 0; //工作
	virtual bool isWorking() = 0;//是否能工作(僵尸出来之后或者土豆雷出生之后)
	//播放死亡动画&清理内存
	virtual void Die() = 0; 
	//被攻击之后的动画以及效果（爆炸等）
	virtual void Attacked() = 0;
};