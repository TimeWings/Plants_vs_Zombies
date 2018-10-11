#include "test.h"
#include "Global.h"

test::test()
{
	Sprite* sp=Sprite::create("peaShooter.png");
	testMap.insert(this,sp);
	
}
