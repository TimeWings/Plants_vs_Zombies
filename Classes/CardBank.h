#pragma once
#include "Entity.h"
#include "EntityLayer.h"

class CardBank:public Entity
{
public:
	CardBank();
	~CardBank();
	void show();
	void hide();
	void clear();
	static void updateSunLabel();

	static CardBank* getInstance()
	{
		if (instance == nullptr)
			instance = new CardBank();
		return instance;
	}

private:
	static CardBank* instance;
	static cocos2d::Label* sunLabel;
};