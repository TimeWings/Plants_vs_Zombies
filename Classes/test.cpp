//#include "test.h"
//#include "Global.h"
//#include "PlantsEnum.h"
//#include "Background.h"
//#include "Loading.h"
//#include "AllEntity.h"
//#include "MenuButton.h"
//#include <iostream>
//#include <typeinfo>
//using namespace map;
//test::test()
//{
//	//auto titleScene = new TitleScene();
//	//Director::getInstance()->replaceScene(titleScene);
//	//Director::getInstance()->runWithScene(new TitleScene());
//	//new Loading();
//	//PlantsEnum::type plantsEnum = PlantsEnum::PeaShooter;
//	//std::cout << PlantsEnum::ToString(plantsEnum) << std::endl;
//
//	CardBank::getInstance()->show();
//
//	MenuButton::addListener();
//	MenuButton::enable();
//
//	GameStart = true;
//	drawRect();
//
//	sunCnt.first = 9999;
//	CardBank::updateSunLabel();
//	auto s = Director::getInstance()->getWinSize();
//
//	new Card<IceShooter>(Point(20, 300));
//	new Card<Mushroom>(Point(40, 300));
//	new Card<PeaShooter>(Point(60, 300));
//	new Card<Melancholy>(Point(80, 300));
//	new Card<Sunflower>(Point(100, 300));
//	new Card<Weeds>(Point(120, 300));
//	new Card<NutPlus>(Point(140, 300));
//	new Card<Doom_shroom>(Point(160, 300));
//	new Card<JannuDaruku>(Point(180, 300));
//	new Card<StarShooter>(Point(200, 300));
//	new Card<TripleShooter>(Point(220, 300));
//	new Card<iceCabbage>(Point(240, 300));
//	new Card<Torch>(Point(260, 300));
//	new Card<Cushaw>(Point(280, 300));
//	new Card<Chomper>(Point(300, 300));
//	new Card<PotatoMine>(Point(320, 300));
//	new Card<Pumpkin>(Point(340, 300));
//	new Card<Lucker>(Point(360, 300));
//	new Card<DoublePeaShooter>(Point(380, 300));
//	new Card<Lancer>(Point(400, 300));
//	new ZombieCard<RoadblockZombie>(Point(420, 300));
//	new ZombieCard<BasicZombie>(Point(440, 300));
//	new Card<Shovel>(Point(460, 300));
//	new Card<Nut>(Point(20, 260));
//	new Card<Landslock>(Point(40, 260));
//	new Card<riceShooter>(Point(60, 260));
//	new Card<Paul>(Point(80, 260));
//	new Card<Lotus>(Point(20, 220));
//	new Card<Lantern>(Point(40, 220));
//	new Card<Clover>(Point(60, 220));
//	new Card<Magnet>(Point(80, 220));
//	new Card<Tomb>(Point(20, 180));
//	new Card<GraveBuster>(Point(40, 180));
//	new ZombieCard<Zomboni>(Point(60, 180));
//	new Card<Ladder>(Point(80, 180));
//	new ZombieCard<NewspaperZombie>(Point(20, 140));
//	new Card<HeroThunder>(Point(40, 140));
//	new ZombieCard<DoorZombie>(Point(60, 140));
//	new Card<HeroLucker>(Point(80, 140));
//	new ZombieCard<PoleVaultingZombie>(Point(20, 100));
//	new ZombieCard<BucketZombie>(Point(40, 100));
//	new ZombieCard<FootBallZombie>(Point(60, 100));
//	new Card<SmallMushRoom>(Point(80, 100));
//	new ZombieCard<BombZombie>(Point(20, 60));
//	new Card<WhiteJannu>(Point(40, 60));
//	new Card<Thunder>(Point(60, 60));
//	new Card<WaterShooter>(Point(80, 60));
//	new ZombieCard<Gargantuar>(Point(100, 60));
//	new ZombieCard<ImpZombie>(Point(20, 20));
//	new ZombieCard<MinerZombie>(Point(40, 20));
//	new ZombieCard<DuckZombie>(Point(60, 20));
//	
//}
//void test::drawRect()
//{
//	DrawNode* drawNode = DrawNode::create();
//	EntityLayer* bl = EntityLayer::getInstance();
//	
//	for (int i = 1; i <=MapRow; i++)
//	{
//		for (int j = 1; j <= MapCol; j++)
//		{
//			Vec2 point[4];
//			Point Center = Rank2Point(i, j);
//			point[0] = Point(Center.x-BlockSize.first/2,Center.y-BlockSize.second/2);
//			point[1] = Point(Center.x - BlockSize.first / 2, Center.y + BlockSize.second / 2);
//			point[2] = Point(Center.x + BlockSize.first / 2, Center.y + BlockSize.second / 2);
//			point[3] = Point(Center.x + BlockSize.first / 2, Center.y - BlockSize.second / 2);
//
//			//绘制空心多边形
//			//填充颜色：Color4F(1, 0, 0, 0), 透明
//			//轮廓颜色：Color4F(0, 1, 0, 1), 绿色
//			drawNode->drawPolygon(point, 4, Color4F(1, 0, 0, 0), 1, Color4F(0, 1, 0, 1));
//			//std::cout << "hahahahah" << std::endl;
//		}
//	}
//	bl->addChild(drawNode,100);
//}