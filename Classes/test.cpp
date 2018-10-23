#include "test.h"
#include "Global.h"
#include "IceShooter.h"
#include "BasicZombie.h"
#include "Plants.h"
#include "Weeds.h"
#include <iostream>


test::test()
{
	Plants* plant1 = new Weeds(Point(60, 120),3);                                                             
	Zombie* zombie1 = new BasicZombie(Point(360, 60), 3); 
	/*Plants* plant2 = new IceShooter(Point(60, 80));
	Plants* plant3 = new IceShooter(Point(60, 100));
	Plants* plant4 = new IceShooter(Point(60, 120));
	Plants* plant5 = new IceShooter(Point(60, 140));*/
}
