#include "CardEntity.h"

void CardEntity::setCost()
{
	if (plantsTypeName == "PotatoMine" || plantsTypeName == "Lotus" || plantsTypeName == "Lantern" || plantsTypeName == "SmallMushRoom")
	{
		cost = 25;
	}
	else if (plantsTypeName == "Sunflower" || plantsTypeName == "Nut" || plantsTypeName == "Pumpkin")
	{
		cost = 50;
	}
	else if (plantsTypeName == "GraveBuster" || plantsTypeName == "Landslock" || plantsTypeName == "Mushroom")
	{
		cost = 75;
	}
	else if (plantsTypeName == "PeaShooter" || plantsTypeName == "Lucker" || plantsTypeName == "Clover" ||
		plantsTypeName == "Magnet"  || plantsTypeName == "Lancer")
	{
		cost = 100;
	}

	else if (plantsTypeName == "NutPlus" || plantsTypeName == "Cushaw" || plantsTypeName == "WaterShooter" || plantsTypeName == "riceShooter"
		|| plantsTypeName == "JannuDaruku" || plantsTypeName == "StarShooter")
	{
		cost = 125;
	}
	else if (plantsTypeName == "Doom_shroom" || plantsTypeName == "Chomper" || plantsTypeName == "Weeds" || plantsTypeName == "HeroLucker"
		|| plantsTypeName == "iceCabbage")
	{
		cost = 150;
	}
	else if (plantsTypeName == "IceShooter" || plantsTypeName == "Torch" || plantsTypeName == "Melancholy" )
	{
		cost = 175;
	}
	else if (plantsTypeName == "Thunder" || plantsTypeName == "DoublePeaShooter")
	{
		cost = 200;
	}
	else if (plantsTypeName == "WhiteJannu")
	{
		cost = 225;
	}
	else if (plantsTypeName == "TripleShooter")
	{
		cost = 325;
	}
	else if (plantsTypeName == "HeroThunder")
	{
		cost = 450;
	}
	else if (plantsTypeName == "Paul")
	{
		cost = 500;
	}
}
