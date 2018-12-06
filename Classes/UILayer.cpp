#include "UILayer.h"



UILayer::UILayer()
{
}


UILayer::~UILayer()
{
}

UILayer* UILayer::pRet = NULL;
UILayer* UILayer::create()
{
	UILayer::pRet = new UILayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool UILayer::init()
{
	this->setTouchEnabled(true);
	return true;
}