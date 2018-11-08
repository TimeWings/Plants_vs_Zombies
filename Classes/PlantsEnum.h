#pragma once

//#include <string>
//namespace stringable_enum_utils
//{
//	std::string findStringInArgs(const char* args, int index) {   //index begin from 0
//		// find begin of enum string
//		int pos = 0;
//		for (int i = 0; i < index; pos++) {   // pos record the begining of enum string
//			if (args[pos] == ',') i++;
//		}
//		while (args[pos] == ',' || args[pos] == ' ' || args[pos] == '\n' || args[pos] == '\r') pos++;
//		int begin = pos;
//		while (args[pos] != ','&&args[pos] != ' '&&args[pos] != '\n'&&args[pos] != '\r'&&args[pos] != '\0') pos++;
//		return std::string(args).substr(begin, pos - begin);
//	}
//}//stringable_enum_utils
//
//#define STRING_ABLE_ENUM(name,...)\
//    class name{\
//    public:\
//        virtual void _virtual_flag() = 0;\
//        enum _realenum{__VA_ARGS__};\
//        typedef enum name::_realenum type;\
//        static std::string ToString(name::type _enum){\
//            return stringable_enum_utils::findStringInArgs(#__VA_ARGS__,_enum);\
//        }\
//    };
//STRING_ABLE_ENUM
//(
//	PlantsEnum,
//	IceShooter,
//	Mushroom,
//	PeaShooter,
//	Melancholy,
//	Sunflower,
//	Weeds,
//	NutPlus,
//	Doom_shroom,
//	JannuDaruku,
//	StarShooter,
//	TripleShooter,
//	iceCabbage,
//	Torch,
//	Cushaw,
//	Chomper,
//	PotatoMine,
//	Pumpkin,
//	Lucker,
//	DoublePeaShooter,
//	Lancer,
//	Shovel,
//	Nut,
//	Landslock,
//	riceShooter,
//	Paul,
//	HeroLucker,
//	Lotus,
//	Lantern,
//);
enum class PlantsEnum
{
	IceShooter,
	Mushroom,
	PeaShooter,
	Melancholy,
	Sunflower,
	Weeds,
	NutPlus,
	Doom_shroom,
	JannuDaruku,
	StarShooter,
	TripleShooter,
	iceCabbage,
	Torch,
	Cushaw,
	Chomper,
	PotatoMine,
	Pumpkin,
	Lucker,
	DoublePeaShooter,
	Lancer,
	Shovel,
	Nut,
	Landslock,
	riceShooter,
	Paul,
	HeroLucker,
	Lotus,
	Lantern,
	DoorZombie
};

