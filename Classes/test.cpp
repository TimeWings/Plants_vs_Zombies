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
#include "Landslock.h"
#include "riceShooter.h"
#include "Paul.h"
#include <iostream>
#include <typeinfo>
using namespace map;
test::test()
{
	new Background();
	drawRect();
	new Card<IceShooter>(Point(20, 290));
	new Card<Mushroom>(Point(40, 290));
	new Card<PeaShooter>(Point(60, 290));
	new Card<Melancholy>(Point(80, 290));
	new Card<Sunflower>(Point(100, 290));
	new Card<Weeds>(Point(120, 290));
	new Card<NutPlus>(Point(140, 290));
	new Card<Doom_shroom>(Point(160, 290));
	new Card<JannuDaruku>(Point(180, 290));
	new Card<StarShooter>(Point(200, 290));
	new Card<TripleShooter>(Point(220, 290));
	new Card<iceCabbage>(Point(240, 290));
	new Card<Torch>(Point(260, 290));
	new Card<Cushaw>(Point(280, 290));
	new Card<Chomper>(Point(300, 290));
	new Card<PotatoMine>(Point(320, 290));
	new Card<Pumpkin>(Point(340, 290));
	new Card<NutPlus>(Point(360, 290));
	new Card<Lucker>(Point(380, 290));
	new Card<DoublePeaShooter>(Point(400, 290));
	new Card<Lancer>(Point(420, 290));
	new ZombieCard<RoadblockZombie>(Point(440, 290));
	new ZombieCard<BasicZombie>(Point(460, 290));
	new Card<Nut>(Point(20, 250));
	new Card<Landslock>(Point(40, 250));
	new Card<riceShooter>(Point(60, 250));
	new Card<Paul>(Point(80, 250));
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