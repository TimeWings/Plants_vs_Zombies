#include "MainMenu.h"
#include "EntityLayer.h"
#include "Global.h"
#include "FontConfig.h"
#include "LevelManager.h"
#include "ui/CocosGUI.h"
#include "UILayer.h"
using namespace ui;
using namespace map;

MainMenu* MainMenu::instance;

MainMenu::MainMenu()
{
	
}


MainMenu::~MainMenu()
{
}

bool MainMenu::isShow()
{
	return showing;
}

void MainMenu::show()
{
	pauseScene = CCScene::create();
	pauseLayer = Layer::create();
	pauseScene->addChild(pauseLayer, 1);
	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
  //并将Sprite添加到GamePause场景层中
  //得到窗口的大小
	
	auto visibleSize = Director::getInstance()->getWinSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888, GL_DEPTH24_STENCIL8);

	//遍历当前层的所有子节点信息，画入renderTexture中。
	//这里类似截图。
	renderTexture->begin();
	EntityLayer::getInstance()->getParent()->visit();
	renderTexture->end();

	CCSprite *back_spr = CCSprite::createWithTexture(renderTexture->getSprite()->getTexture());
	back_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
	pauseScene->addChild(back_spr);

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	CCDirector::sharedDirector()->pushScene(pauseScene);
	auto camera = Camera::getDefaultCamera();
	camera->pause();
	auto UIlayer = UILayer::getInstance();
	UIlayer->pause();
	auto childerns = UIlayer->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->pause();
	}
	
	auto layer = pauseLayer;
	auto s = Director::getInstance()->getWinSize();
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->addImage("UI\\dialog.png"));
	bg->setAnchorPoint(Point(0.5f, 0.5f));
	bg->setPosition(s.width / 2, s.height / 2 - 20);
	bg->setContentSize(Size(300, 300));
	layer->addChild(bg, 1500);
	setImg(bg);

	closeButton = Button::create("UI\\close.png", "UI\\close.png", "UI\\close.png");
	getImg()->addChild(closeButton);
	closeButton->setPosition(Point(250, 240));
	closeButton->setScale(1.5f);
	closeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			hide();
			break;
		default:
			break;
		}
	});

	retryButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(retryButton);
	retryButton->setPosition(Point(150, 215));
	retryButton->setScale(2.0f);
	auto labelRetry = Label::createWithTTF(*(FontConfig::getInstance()), "Retry");
	labelRetry->setTextColor(Color4B::BLACK);
	labelRetry->setPosition(Point(150, 217));
	labelRetry->setScale(1.5f);
	getImg()->addChild(labelRetry);
	retryButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			hide();
			LevelManager::loadLevel(-1);
			break;
		default:
			break;
		}
	});

	levelButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(levelButton);
	levelButton->setPosition(Point(150, 185));
	levelButton->setScale(2.0f);
	auto labelLevel = Label::createWithTTF(*(FontConfig::getInstance()), "Level");
	labelLevel->setTextColor(Color4B::BLACK);
	labelLevel->setPosition(Point(150, 187));
	labelLevel->setScale(1.5f);
	getImg()->addChild(labelLevel);
	levelButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			hide();
			LevelManager::getInstance()->show();
			break;
		default:
			break;
		}
	});

	exitButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(exitButton);
	exitButton->setPosition(Point(150, 155));
	exitButton->setScale(2.0f);
	auto labelExit = Label::createWithTTF(*(FontConfig::getInstance()), "Exit");
	labelExit->setTextColor(Color4B::BLACK);
	labelExit->setPosition(Point(150, 157));
	labelExit->setScale(1.5f);
	getImg()->addChild(labelExit);
	exitButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			exit(0);
			break;
		default:
			break;
		}
	});

	FadeIn* fadein = FadeIn::create(0.3f);
	getImg()->setOpacity(0);
	getImg()->runAction(fadein);
	childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->setOpacity(0);
		childerns.at(i)->runAction(fadein->clone());
	}
	retryButton->setEnabled(true);
	levelButton->setEnabled(true);
	exitButton->setEnabled(true);
	closeButton->setEnabled(true);
	showing = true;
}

void MainMenu::hide()
{
	
	FadeOut* fadeout = FadeOut::create(0.3f);
	getImg()->runAction(fadeout);
	auto childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->runAction(fadeout->clone());
	}
	retryButton->setEnabled(false);
	levelButton->setEnabled(false);
	exitButton->setEnabled(false);
	closeButton->setEnabled(false);
	showing = false;
	CCDirector::sharedDirector()->popScene();
	auto camera = Camera::getDefaultCamera();
	camera->resume();
	auto UIlayer = UILayer::getInstance();
	UIlayer->resume();
	childerns = UIlayer->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->resume();
	}
}

void MainMenu::clear()
{
	//retryButton->removeFromParent();
	//levelButton->removeFromParent();
	//exitButton->removeFromParent();
	//closeButton->removeFromParent();
	//getImg()->removeFromParent();
	delete instance;
	instance = nullptr;
	//if (pauseLayer != nullptr)
	//	pauseLayer->removeFromParent();
	//if (pauseScene != nullptr)
	//	pauseScene->removeFromParent();
}