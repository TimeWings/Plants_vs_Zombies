#include "FontConfig.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

TTFConfig* FontConfig::instance;

TTFConfig* FontConfig::create()
{
	TTFConfig* config = new TTFConfig();
	config->fontFilePath = "Font\\TianShiYanTi.ttf";
	config->fontSize = 5.0f;
	return config;
}