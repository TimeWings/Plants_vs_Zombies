#include "test.h"
#include "Global.h"
#include "PlantsEnum.h"
#include "Background.h"
#include "Loading.h"
#include "IceShooter.h"
#include "PotatoMine.h"
#include "Pumpkin.h"
#include "BasicZombie.h"
#include "Plants.h"
#include "DoublePeaShooter.h"
#include "RoadblockZombie.h"
#include "Mushroom.h"
#include "Weeds.h"
#include "NutPlus.h"
#include "Melancholy.h"
#include "Sunflower.h"
#include "Doom_shroom.h"
#include "JannuDaruku.h"
#include "StarShooter.h"
#include "TripleShooter.h"
#include "iceCabbage.h"
#include "Card.h"
#include "SelectCard.h"
#include "UnSelectCard.h"
#include "ZombieCard.h"
#include "Torch.h"
#include "Cushaw.h"
#include "Chomper.h"
#include "Lucker.h"
#include "Lancer.h"
#include "Lotus.h"
#include "Magnet.h"
#include "Landslock.h"
#include "riceShooter.h"
#include "HeroLucker.h"
#include "Paul.h"
#include "WhiteJannu.h"
#include "Shovel.h"
#include "Lantern.h"
#include "DoorZombie.h"
#include "Clover.h"
#include "Magnet.h"
#include "Tomb.h"
#include "GraveBuster.h"
#include "NewspaperZombie.h"
#include "ui/CocosGUI.h"
#include "GameStartButton.h"
#include "PoleVaultingZombie.h"
#include "Zomboni.h"
#include "SmallMushRoom.h"
#include "Title.h"
#include "FootBallZombie.h"
#include "SelectCardBG.h"
#include "Thunder.h"
#include "BucketZombie.h"
#include "BombZombie.h"
#include "Gargantuar.h"
#include <iostream>
#include <typeinfo>
using namespace map;
test::test()
{
	//auto titleScene = new TitleScene();
	//Director::getInstance()->replaceScene(titleScene);
	//Director::getInstance()->runWithScene(new TitleScene());
	//new Loading();
	//PlantsEnum::type plantsEnum = PlantsEnum::PeaShooter;
	//std::cout << PlantsEnum::ToString(plantsEnum) << std::endl;
	/*
	new SelectCardBG();
	float startX = -1.0f;
	float startY = 200.0f;
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
	startX = 0;
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
	startX = 0;
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
	auto unSelectCard21 = new UnSelectCard<Shovel>(Point(startX += offsetX, startY), PlantsEnum::Shovel);
	unSelectingCardsEntity.push_back(unSelectCard21);
	startX = 0;
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
	startX = 0;
	startY -= offsetY;
	auto unSelectCard29 = new UnSelectCard<Magnet>(Point(startX += offsetX, startY), PlantsEnum::Magnet);
	unSelectingCardsEntity.push_back(unSelectCard29);

	new GameStartButton(Point(120, 15));
	*/
	GameStart = true;
	drawRect();
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
	new Card<GraveBuster>(Point(80, 180));
	new ZombieCard<NewspaperZombie>(Point(20, 140));
	new Card<HeroLucker>(Point(40, 140));
	new ZombieCard<DoorZombie>(Point(60, 140));
	new Card<HeroLucker>(Point(80, 140));
	new ZombieCard<PoleVaultingZombie>(Point(20, 100));
	new ZombieCard<BucketZombie>(Point(40, 100));
	new ZombieCard<FootBallZombie>(Point(60, 100));
	new Card<SmallMushRoom>(Point(80, 100));
	new ZombieCard<BombZombie>(Point(20, 60));
	new Card<WhiteJannu>(Point(80, 100));
	new Card<Thunder>(Point(100, 100));
	new ZombieCard<Gargantuar>(Point(40, 60));
}
void test::drawRect()
{
	DrawNode* drawNode = DrawNode::create();
	EntityLayer* bl = EntityLayer::getInstance();
	
	for (int i = 1; i <=MapRow; i++)
	{
		for (int j = 1; j <= MapCol; j++)
		{
			Vec2 point[4];
			Point Center = Rank2Point(i, j);
			point[0] = Point(Center.x-BlockSize.first/2,Center.y-BlockSize.second/2);
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
	bl->addChild(drawNode,100);
}