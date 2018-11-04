#include "test.h"
#include "Global.h"
#include "Background.h"
#include "Plantable.h"
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
#include "Torch.h"
#include "Cushaw.h"
#include "Chomper.h"
#include <iostream>
#include <typeinfo>
using namespace map;

test::test()
{
	new Background();
	//Plants* plant1 = new Weeds(Point(60, 120),4);      
	/*new BasicZombie(Rank2Point(6, 6), 6, 6);
	new BasicZombie(Rank2Point(5, 6), 5, 6);
	new BasicZombie(Rank2Point(4, 6), 4, 6);
	new BasicZombie(Rank2Point(3, 6), 3, 6);
	new BasicZombie(Rank2Point(2, 6), 2, 6);
	new BasicZombie(Rank2Point(1, 6), 1, 6);*/
	//new RoadblockZombie(Rank2Point(6, 6), 6, 6);
	new RoadblockZombie(Rank2Point(5, 6), 5, 6);
	new RoadblockZombie(Rank2Point(4, 6), 4, 6);
	new RoadblockZombie(Rank2Point(3, 6), 3, 6);
	new RoadblockZombie(Rank2Point(2, 6), 2, 6);
	new RoadblockZombie(Rank2Point(1, 6), 1, 6);
	//new BasicZombie(Rank2Point(3, 4), 3, 4);
	//new BasicZombie(Rank2Point(3, 10), 3, 10);
	//new BasicZombie(Rank2Point(3, 6), 3, 6);
	//Zombie* zombie2 = new BasicZombie(Point(120, 60), 4); 
	//Plants* plant1 = new PotatoMine(Point(100, 60), 4);
	//Plants* plant2 = new Weeds(Point(60, 250),1);
	//std::cout << Rank2Point(1, 1).x<<"	" <<Rank2Point(1, 1).y << std::endl;
	//new Melancholy(Rank2Point(4, 3), 4, 3);
	//new TripleShooter(Rank2Point(4, 1), 4, 1);
	/*new TripleShooter(Rank2Point(3, 3), 3, 3);
	new Torch(Rank2Point(4, 6), 4, 6);
	new Torch(Rank2Point(3, 6), 3, 6);
	new Torch(Rank2Point(2, 6), 2, 6);*/
	//Plants* plant4 = new IceShooter(Point(60, 120),1,1);
	//Plants* plant5 = new IceShooter(Point(60, 120),3);
	//Plants* plant5 = new Mushroom(Point(200, 120), 3);
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 5; j++)
		{
			auto plant = new Plantable(Point(75 + 38.5f * i, -5 + 45.0f*j - 3));
			plant->row = 6-j;
			plant->col = 10-i;
			plantableList.push_back(plant);
		}
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
	//Card<Mushroom>* card = new Card<Mushroom>(Point(200, 300), 3);
	//Card<PeaShooter>* card2 = new Card<PeaShooter>(Point(300, 300), 3);
	//card->BindPlant<Mushroom>();
	//card->PutPlant<Mushroom>(Point(100, 200), 3);
}
