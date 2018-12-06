#pragma once
#include "cocos2d.h"

class UILayer : public cocos2d::Layer
{
public:
	UILayer();
	~UILayer();
	virtual bool init();
	static UILayer* create();
	static UILayer* getInstance()
	{
		if (pRet == nullptr)
			pRet = create();
		return pRet;
	}
	static UILayer *pRet;
};

