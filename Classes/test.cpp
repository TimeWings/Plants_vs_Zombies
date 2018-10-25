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
#include <iostream>


test::test()
{
	//Plants* plant1 = new Weeds(Point(60, 120),4);      
	Zombie* zombie1 = new BasicZombie(Point(360, 120), 3);
	//Zombie* zombie2 = new BasicZombie(Point(120, 60), 4); 
	//Plants* plant1 = new PotatoMine(Point(100, 60), 4);
	//Plants* plant2 = new Weeds(Point(60, 250),1);
	/*Plants* plant3 = new IceShooter(Point(60, 100));
	Plants* plant4 = new IceShooter(Point(60, 120));*/
	//Plants* plant5 = new IceShooter(Point(60, 120),3);
	Plants* plant5 = new Mushroom(Point(200, 120), 3);
}
