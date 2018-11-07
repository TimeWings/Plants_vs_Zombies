#include "test.h"
#include "Global.h"
#include "Background.h"
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
#include "ZombieCard.h"
#include "Torch.h"
#include "Cushaw.h"
#include "Chomper.h"
#include "Lucker.h"
#include "Lancer.h"
#include "Lotus.h"
#include "Landslock.h"
#include "riceShooter.h"
#include "HeroLucker.h"
#include "Paul.h"
#include "Shovel.h"
#include <iostream>
#include <typeinfo>
using namespace map;
test::test()
{
	new Background();
	drawRect();
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
	new Card<HeroLucker>(Point(100, 260));
	new Card<Lotus>(Point(20, 220));
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