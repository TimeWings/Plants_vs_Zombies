#include "test.h"
#include "Global.h"
#include "IceShooter.h"
#include "PotatoMine.h"
#include "Pumpkin.h"
#include "BasicZombie.h"
#include "Plants.h"
#include "DoublePeaShooter.h"
#include "Mushroom.h"
#include "Weeds.h"
#include "Sunflower.h"
#include "Card.h"
#include <iostream>
#include <typeinfo>
using namespace map;
test::test()
{
	//Plants* plant1 = new Weeds(Point(60, 120),4);      
	//Zombie* zombie1 = new BasicZombie(Point(360, 120), 3);
	//Zombie* zombie2 = new BasicZombie(Point(120, 60), 4); 
	//Plants* plant1 = new PotatoMine(Point(100, 60), 4);
	//Plants* plant2 = new Weeds(Point(60, 250),1);
	//std::cout << Rank2Point(1, 1).x<<"	" <<Rank2Point(1, 1).y << std::endl;
	Plants* plant3 = new IceShooter(Rank2Point(6,1),6,1);
	//Plants* plant4 = new IceShooter(Point(60, 120),1,1);
	//Plants* plant5 = new IceShooter(Point(60, 120),3);
	//Plants* plant5 = new Mushroom(Point(200, 120), 3);
	//Card<Mushroom>* card = new Card<Mushroom>(Point(100, 100), 3);
	//Card<Mushroom>* card = new Card<Mushroom>(Point(200, 300), 3);
	//Card<PeaShooter>* card2 = new Card<PeaShooter>(Point(300, 300), 3);
	//card->BindPlant<Mushroom>();
	//card->PutPlant<Mushroom>(Point(100, 200), 3);
}
