#include "LevelManager.h"
#include "FontConfig.h"
#include "Background.h"
#include "ui/CocosGUI.h"
#include "Global.h"
#include "SelectCardBG.h"
#include "MenuButton.h"
#include "GameStartButton.h"
#include "CardBank.h"
#include "LevelManager.h"
#include "MenuButton.h"
#include "MainMenu.h"
#include "AllEntity.h"
#include "Shovel.h"
#include "Global.h"
#include "HelloWorldScene.h"
#include "UILayer.h"
#include "ZombieEnum.h"
#include "WinMenu.h"
#include "LoseMenu.h"

using namespace ui;
using namespace map;

LevelManager* LevelManager::instance = nullptr;
Card<Shovel>* LevelManager::shovel = nullptr;
int LevelManager::currentLevel = 1;
int LevelManager::bg[16] = { -1,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4 };
int LevelManager::kill = 0;
int LevelManager::zombieCount = 0;
int LevelManager::zombie[16][36] =
{
	{0},
	{15,0,0,0,1,1,0,2,1,0,2,1,0,2,1,3},
	{20,0,0,0,1,1,2,6,2,3,6,3,1,6,2,0,1,3,0,6,5},
	{25,0,0,0,1,1,2,0,9,3,3,2,1,6,7,0,5,7,1,9,2,6,0,8,8,9},

	{15,0,0,0,1,1,4,4,1,2,4,0,3,2,6,6},
	{20,0,0,1,1,2,4,4,6,5,4,6,7,4,4,9,7,9,3,4,2},
	{25,0,0,1,1,2,4,6,4,5,4,7,6,2,8,3,10,8,0,1,9,4,9,7,7,10},

	{15,0,0,1,1,2,2,3,11,11,7,6,2,6,7},
	{20,0,0,1,1,2,3,11,11,6,6,5,7,8,2,11,9,9,3,5,10},
	{25,0,0,1,1,2,3,6,5,6,11,11,7,3,11,9,9,2,1,0,3,3,5,12},

	{15,0,0,1,1,2,2,3,6,6,5,3,11,11,11},
	{20,0,0,1,2,2,3,5,6,6,7,7,8,11,11,11,5,9,9,6,12},
	{25,0,0,1,1,2,2,3,3,5,6,6,5,7,8,8,9,9,11,11,10,11,11,12,12},

	{10,0,0,0,0,1,1,2,1,3,6},
	{15,0,0,0,1,1,2,2,3,6,6,0,2,11,10},
	{20,0,0,1,1,6,2,3,3,6,6,5,5,0,3,2,1,7,7,3,12}
};

LevelManager::LevelManager()
{
	auto layer = UILayer::getInstance();
	auto s = Director::getInstance()->getWinSize();
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->addImage("UI\\dialog.png"));
	bg->setAnchorPoint(Point(0.5f, 0.5f));
	bg->setPosition(s.width/2, s.height/2-20);
	bg->setContentSize(Size(300, 300));
	layer->addChild(bg, 1500);
	setImg(bg);

	closeButton = Button::create("UI\\close.png", "UI\\close.png", "UI\\close.png");
	getImg()->addChild(closeButton);
	closeButton->setPosition(Point(250,240));
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
	int startX = 90;
	int startY = 215;
	int offsetX = 30;
	int offsetY = 30;
	int x, y;
	for (int i = 0; i < totalLevelCount; i++)
	{
		x = startX + i % 5 * offsetX;
		y = startY - i / 5 * offsetY;
		auto button = Button::create("UI\\LevelButton.png", "UI\\LevelButton.png", "UI\\LevelButton.png");
		button->setPosition(Point(x, y));
		button->setScale(0.5f);
		getImg()->addChild(button);
		auto label = Label::createWithTTF(*FontConfig::getInstance(), std::to_string(i + 1));
		label->setPosition(Point(x-0.5f, y+2.5f));
		label->setScale(1.5f);
		label->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
		getImg()->addChild(label);

		button->addTouchEventListener([&,i](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				//std::cout << i << std::endl;
				//currentLevel = i + 1;
				hide();
				LevelManager::loadLevel(i+1);
				break;
			default:
				break;
			}
		});
		buttons.push_back(button);
	}
}

LevelManager::~LevelManager()
{

}

bool LevelManager::isShow()
{
	return showing;
}

void LevelManager::show()
{
	FadeIn* fadein = FadeIn::create(0.3f);
	getImg()->setOpacity(0);
	getImg()->runAction(fadein);
	auto childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->setOpacity(0);
		childerns.at(i)->runAction(fadein->clone());
	}
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->setEnabled(true);
	closeButton->setEnabled(true);
	showing = true;
}

void LevelManager::hide()
{
	FadeOut* fadeout = FadeOut::create(0.3f);
	getImg()->runAction(fadeout);
	auto childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->runAction(fadeout->clone());
	}
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->setEnabled(false);
	closeButton->setEnabled(true);
	showing = false;
}

void LevelManager::clear()
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->removeFromParent();
	buttons.clear();
	closeButton->removeFromParent();
	getImg()->removeFromParent();
	delete instance;
	instance = nullptr;
}

void LevelManager::clearAllUI()
{
	SelectCardBG::getInstance()->clear();
	CardBank::getInstance()->clear();
	MainMenu::getInstance()->clear();
	getInstance()->clear();
	GameStartButton::clear();
	MenuButton::clear();
	WinMenu::getInstance()->clear();
	LoseMenu::getInstance()->clear();

}

void LevelManager::showAllUI()
{
	
	CardBank::getInstance()->show();
	
	MenuButton::addListener();
	MenuButton::enable();
}

void LevelManager::showSelectCard()
{
	SelectCardBG::getInstance()->show();
	GameStartButton::addListener();
	GameStartButton::enable();
	createAllCard();
}

void LevelManager::gameStart()
{
	GameStart = true;
	auto scene = Director::getInstance()->getRunningScene();
	scene->scheduleOnce(schedule_selector(HelloWorld::updateSun), 1.0f);
	scene->schedule(schedule_selector(HelloWorld::updateSun), 5.0f);
	scene->schedule(schedule_selector(HelloWorld::updateZombie), 12.0f);
	scene->schedule(schedule_selector(HelloWorld::updateCD), 0.1f);
	scene->schedule(schedule_selector(HelloWorld::checkWinAndLose), 1.0f);
}

void LevelManager::createAllCard()
{
	float startX = 5.0f;
	float startY = 230.0f;
	float offsetX = 28.0f;
	float offsetY = 40.0f;
	auto unSelectCard1 = new UnSelectCard<PeaShooter>(Point(startX += offsetX, startY), PlantsEnum::PeaShooter);
	unSelectingCardsEntity.push_back(unSelectCard1);
	auto unSelectCard2 = new UnSelectCard<IceShooter>(Point(startX += offsetX, startY), PlantsEnum::IceShooter);
	unSelectingCardsEntity.push_back(unSelectCard2);
	auto unSelectCard3 = new UnSelectCard<Mushroom>(Point(startX += offsetX, startY), PlantsEnum::Mushroom);
	unSelectingCardsEntity.push_back(unSelectCard3);
	auto unSelectCard4 = new UnSelectCard<Melancholy>(Point(startX += offsetX, startY), PlantsEnum::Melancholy);
	unSelectingCardsEntity.push_back(unSelectCard4);
	auto unSelectCard5 = new UnSelectCard<Sunflower>(Point(startX += offsetX, startY), PlantsEnum::Sunflower);
	unSelectingCardsEntity.push_back(unSelectCard5);
	auto unSelectCard6 = new UnSelectCard<Weeds>(Point(startX += offsetX, startY), PlantsEnum::Weeds);
	unSelectingCardsEntity.push_back(unSelectCard6);
	auto unSelectCard7 = new UnSelectCard<NutPlus>(Point(startX += offsetX, startY), PlantsEnum::NutPlus);
	unSelectingCardsEntity.push_back(unSelectCard7);
	startX = 5;
	startY -= offsetY;
	auto unSelectCard8 = new UnSelectCard<Doom_shroom>(Point(startX += offsetX, startY), PlantsEnum::Doom_shroom);
	unSelectingCardsEntity.push_back(unSelectCard8);
	auto unSelectCard9 = new UnSelectCard<JannuDaruku>(Point(startX += offsetX, startY), PlantsEnum::JannuDaruku);
	unSelectingCardsEntity.push_back(unSelectCard9);
	auto unSelectCard10 = new UnSelectCard<StarShooter>(Point(startX += offsetX, startY), PlantsEnum::StarShooter);
	unSelectingCardsEntity.push_back(unSelectCard10);
	auto unSelectCard11 = new UnSelectCard<TripleShooter>(Point(startX += offsetX, startY), PlantsEnum::TripleShooter);
	unSelectingCardsEntity.push_back(unSelectCard11);
	auto unSelectCard12 = new UnSelectCard<iceCabbage>(Point(startX += offsetX, startY), PlantsEnum::iceCabbage);
	unSelectingCardsEntity.push_back(unSelectCard12);
	auto unSelectCard13 = new UnSelectCard<Torch>(Point(startX += offsetX, startY), PlantsEnum::Torch);
	unSelectingCardsEntity.push_back(unSelectCard13);
	auto unSelectCard14 = new UnSelectCard<Cushaw>(Point(startX += offsetX, startY), PlantsEnum::Cushaw);
	unSelectingCardsEntity.push_back(unSelectCard14);
	startX = 5;
	startY -= offsetY;
	auto unSelectCard15 = new UnSelectCard<Chomper>(Point(startX += offsetX, startY), PlantsEnum::Chomper);
	unSelectingCardsEntity.push_back(unSelectCard15);
	auto unSelectCard16 = new UnSelectCard<PotatoMine>(Point(startX += offsetX, startY), PlantsEnum::PotatoMine);
	unSelectingCardsEntity.push_back(unSelectCard16);
	auto unSelectCard17 = new UnSelectCard<Pumpkin>(Point(startX += offsetX, startY), PlantsEnum::Pumpkin);
	unSelectingCardsEntity.push_back(unSelectCard17);
	auto unSelectCard18 = new UnSelectCard<Lucker>(Point(startX += offsetX, startY), PlantsEnum::Lucker);
	unSelectingCardsEntity.push_back(unSelectCard18);
	auto unSelectCard19 = new UnSelectCard<DoublePeaShooter>(Point(startX += offsetX, startY), PlantsEnum::DoublePeaShooter);
	unSelectingCardsEntity.push_back(unSelectCard19);
	auto unSelectCard20 = new UnSelectCard<Lancer>(Point(startX += offsetX, startY), PlantsEnum::Lancer);
	unSelectingCardsEntity.push_back(unSelectCard20);
	auto unSelectCard21 = new UnSelectCard<Clover>(Point(startX += offsetX, startY), PlantsEnum::Clover);
	unSelectingCardsEntity.push_back(unSelectCard21);
	startX = 5;
	startY -= offsetY;
	auto unSelectCard22 = new UnSelectCard<Nut>(Point(startX += offsetX, startY), PlantsEnum::Nut);
	unSelectingCardsEntity.push_back(unSelectCard22);
	auto unSelectCard23 = new UnSelectCard<Landslock>(Point(startX += offsetX, startY), PlantsEnum::Landslock);
	unSelectingCardsEntity.push_back(unSelectCard23);
	auto unSelectCard24 = new UnSelectCard<riceShooter>(Point(startX += offsetX, startY), PlantsEnum::riceShooter);
	unSelectingCardsEntity.push_back(unSelectCard24);
	auto unSelectCard25 = new UnSelectCard<Paul>(Point(startX += offsetX, startY), PlantsEnum::Paul);
	unSelectingCardsEntity.push_back(unSelectCard25);
	auto unSelectCard26 = new UnSelectCard<HeroLucker>(Point(startX += offsetX, startY), PlantsEnum::HeroLucker);
	unSelectingCardsEntity.push_back(unSelectCard26);
	auto unSelectCard27 = new UnSelectCard<Lotus>(Point(startX += offsetX, startY), PlantsEnum::Lotus);
	unSelectingCardsEntity.push_back(unSelectCard27);
	auto unSelectCard28 = new UnSelectCard<Lantern>(Point(startX += offsetX, startY), PlantsEnum::Lantern);
	unSelectingCardsEntity.push_back(unSelectCard28);
	startX = 5;
	startY -= offsetY;
	auto unSelectCard29 = new UnSelectCard<Magnet>(Point(startX += offsetX, startY), PlantsEnum::Magnet);
	unSelectingCardsEntity.push_back(unSelectCard29);
	auto unSelectCard30 = new UnSelectCard<GraveBuster>(Point(startX += offsetX, startY), PlantsEnum::GraveBuster);
	unSelectingCardsEntity.push_back(unSelectCard30);
	auto unSelectCard31 = new UnSelectCard<HeroThunder>(Point(startX += offsetX, startY), PlantsEnum::HeroThunder);
	unSelectingCardsEntity.push_back(unSelectCard31);
	auto unSelectCard32 = new UnSelectCard<SmallMushRoom>(Point(startX += offsetX, startY), PlantsEnum::SmallMushRoom);
	unSelectingCardsEntity.push_back(unSelectCard32);
	auto unSelectCard33 = new UnSelectCard<WhiteJannu>(Point(startX += offsetX, startY), PlantsEnum::WhiteJannu);
	unSelectingCardsEntity.push_back(unSelectCard33);
	auto unSelectCard34 = new UnSelectCard<Thunder>(Point(startX += offsetX, startY), PlantsEnum::Thunder);
	unSelectingCardsEntity.push_back(unSelectCard34);
	auto unSelectCard35 = new UnSelectCard<WaterShooter>(Point(startX += offsetX, startY), PlantsEnum::WaterShooter);
	unSelectingCardsEntity.push_back(unSelectCard35);
}

void LevelManager::loadLevel(int level)
{
	init();
	zombieCount = 0;
	kill = 0;
	if (level <= 0)
		level = currentLevel;
	auto scene = Scene::create();
	clearAllUI();
	EntityLayer::getInstance()->removeAllChildrenWithCleanup(true);
	EntityLayer::getInstance()->removeFromParent();
	EntityLayer::create();
	UILayer::getInstance()->removeAllChildrenWithCleanup(true);
	UILayer::getInstance()->removeFromParent();
	UILayer::create();

	scene->addChild(EntityLayer::getInstance());
	scene->addChild(UILayer::getInstance());
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
	currentLevel = level;

	sunCnt.first = 0;
	CardBank::updateSunLabel();
	for (int i = 0; i < readyCards.size(); i++)
		readyCards[i]->clear();
	readyCards.clear();
	if (shovel != nullptr)
		shovel->clear();
	shovel = new Card<Shovel>(Point(460, 300), true);
	Background::type = bg[level];
	background = new Background();

	showAllUI();
#ifdef debug
	test();
#endif
	scene->scheduleOnce(schedule_selector( HelloWorld::moveCameraRight),1.0f);
	scene->unschedule(schedule_selector(HelloWorld::updateSun));
	scene->unschedule(schedule_selector(HelloWorld::updateZombie));
}

void LevelManager::createZombie()
{
	auto scene = Director::getInstance()->getRunningScene();
	if (zombieCount == zombie[currentLevel][0])
	{
		cout << "僵尸已出完，不再出新的僵尸" << endl;
		scene->unschedule(schedule_selector(HelloWorld::updateZombie));
		return;
	}
	auto row = random(1, MapRow);
	if (currentLevel == 4 || currentLevel == 5 || currentLevel == 6)
	{
		while (row == 3 || row == 4)
			row = random(1, MapRow);
	}
	std::cout << row << endl;
	Point position = Rank2Point(row, MapCol);
	position.x += 100;
	position.y += 15;
	
	auto zombieType = zombie[currentLevel][++zombieCount];
	switch (zombieType)
	{
		case 0 :new BasicZombie(position, row, MapCol); break;
		case 1 :new RoadblockZombie(position, row, MapCol); break;
		case 2 :new BucketZombie(position, row, MapCol); break;
		case 3 :new DoorZombie(position, row, MapCol); break;
		case 4 :
			row = random(3, 4);
			position = Rank2Point(row, MapCol);
			position.x += 100;
			position.y += 15;
			new DuckZombie(position, row, MapCol); break;
		case 5:new FootBallZombie(position, row, MapCol); break;
		case 6:new NewspaperZombie(position, row, MapCol); break;
		case 7:new MinerZombie(position, row, MapCol); break;
		case 8:new PoleVaultingZombie(position, row, MapCol); break;
		case 9 :new BombZombie(position, row, MapCol); break;
		case 10 :new Zomboni(position, row, MapCol); break;
		case 11 :new ImpZombie(position, row, MapCol); break;
		case 12:new Gargantuar(position, row, MapCol); break;
	}
}

void LevelManager::checkWin()
{
	auto scene = Director::getInstance()->getRunningScene();
	if (zombieCount == zombie[currentLevel][0] && readyZombies.size() == 0)
	{
		cout << "你赢了，不再出阳光和僵尸" << endl;
		scene->unschedule(schedule_selector(HelloWorld::updateSun));
		scene->unschedule(schedule_selector(HelloWorld::updateZombie));
		scene->unschedule(schedule_selector(HelloWorld::checkWinAndLose));
		
		WinMenu::getInstance()->show();
	}
}

void LevelManager::checkLose()
{
	auto scene = Director::getInstance()->getRunningScene();
	bool isLose = false;
	for (int i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies[i]->getImg()->getPosition().x <= 0)
		{
			isLose = true;
			break;
		}
	}
	if (isLose)
	{
		cout << "你输了，不再出阳光和僵尸" << endl;
		scene->unschedule(schedule_selector(HelloWorld::updateSun));
		scene->unschedule(schedule_selector(HelloWorld::updateZombie));
		scene->unschedule(schedule_selector(HelloWorld::checkWinAndLose));

		LoseMenu::getInstance()->show();
	}
}

void LevelManager::test()
{

	CardBank::getInstance()->show();

	MenuButton::addListener();
	MenuButton::enable();

	GameStart = true;

	sunCnt.first = 9999;
	CardBank::updateSunLabel();
	auto s = Director::getInstance()->getWinSize();

	new Card<IceShooter>(Point(20, 300));
	new Card<Mushroom>(Point(40, 300));
	new Card<PeaShooter>(Point(60, 300));
	new Card<Melancholy>(Point(80, 300));
	new Card<Sunflower>(Point(100, 300));
	new Card<Weeds>(Point(120, 300));
	new Card<NutPlus>(Point(140, 300));
	new Card<Doom_shroom>(Point(160, 300));
	new Card<JannuDaruku>(Point(180, 300));
	new Card<StarShooter>(Point(200, 300));
	new Card<TripleShooter>(Point(220, 300));
	new Card<iceCabbage>(Point(240, 300));
	new Card<Torch>(Point(260, 300));
	new Card<Cushaw>(Point(280, 300));
	new Card<Chomper>(Point(300, 300));
	new Card<PotatoMine>(Point(320, 300));
	new Card<Pumpkin>(Point(340, 300));
	new Card<Lucker>(Point(360, 300));
	new Card<DoublePeaShooter>(Point(380, 300));
	new Card<Lancer>(Point(400, 300));
	new ZombieCard<RoadblockZombie>(Point(420, 300));
	new ZombieCard<BasicZombie>(Point(440, 300));
	new Card<Shovel>(Point(460, 300));
	new Card<Nut>(Point(20, 260));
	new Card<Landslock>(Point(40, 260));
	new Card<riceShooter>(Point(60, 260));
	new Card<Paul>(Point(80, 260));
	new Card<Lotus>(Point(20, 220));
	new Card<Lantern>(Point(40, 220));
	new Card<Clover>(Point(60, 220));
	new Card<Magnet>(Point(80, 220));
	new Card<Tomb>(Point(20, 180));
	new Card<GraveBuster>(Point(40, 180));
	new ZombieCard<Zomboni>(Point(60, 180));
	new Card<Ladder>(Point(80, 180));
	new ZombieCard<NewspaperZombie>(Point(20, 140));
	new Card<HeroThunder>(Point(40, 140));
	new ZombieCard<DoorZombie>(Point(60, 140));
	new Card<HeroLucker>(Point(80, 140));
	new ZombieCard<PoleVaultingZombie>(Point(20, 100));
	new ZombieCard<BucketZombie>(Point(40, 100));
	new ZombieCard<FootBallZombie>(Point(60, 100));
	new Card<SmallMushRoom>(Point(80, 100));
	new ZombieCard<BombZombie>(Point(20, 60));
	new Card<WhiteJannu>(Point(40, 60));
	new Card<Thunder>(Point(60, 60));
	new Card<WaterShooter>(Point(80, 60));
	new ZombieCard<Gargantuar>(Point(100, 60));
	new ZombieCard<ImpZombie>(Point(20, 20));
	new ZombieCard<MinerZombie>(Point(40, 20));
	new ZombieCard<DuckZombie>(Point(60, 20));
	drawRect();
}

void LevelManager::drawRect()
{
	DrawNode* drawNode = DrawNode::create();
	EntityLayer* bl = EntityLayer::getInstance();

	for (int i = 1; i <= MapRow; i++)
	{
		for (int j = 1; j <= MapCol; j++)
		{
			Vec2 point[4];
			Point Center = Rank2Point(i, j);
			point[0] = Point(Center.x - BlockSize.first / 2, Center.y - BlockSize.second / 2);
			point[1] = Point(Center.x - BlockSize.first / 2, Center.y + BlockSize.second / 2);
			point[2] = Point(Center.x + BlockSize.first / 2, Center.y + BlockSize.second / 2);
			point[3] = Point(Center.x + BlockSize.first / 2, Center.y - BlockSize.second / 2);

			//绘制空心多边形
			//填充颜色：Color4F(1, 0, 0, 0), 透明
			//轮廓颜色：Color4F(0, 1, 0, 1), 绿色
			drawNode->drawPolygon(point, 4, Color4F(1, 0, 0, 0), 1, Color4F(0, 1, 0, 1));
			//std::cout << "hahahahah" << std::endl;
		}
	}
	bl->addChild(drawNode, 100);
}