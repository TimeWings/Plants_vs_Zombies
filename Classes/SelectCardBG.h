#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "EntityLayer.h"
using namespace cocos2d;

class SelectCardBG: public Entity
{
public:
	SelectCardBG();
	~SelectCardBG();
	void show();
	void hide();
	void clear();
	static SelectCardBG* getInstance()
	{
		if (instance == nullptr)
			instance = new SelectCardBG();
		return instance;
	}

private:
	static SelectCardBG* instance;
};

