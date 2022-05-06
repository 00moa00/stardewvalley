#pragma once
enum class TILE_COLL {
	INIT,
	NOTACT,
	COll,
	RIGHTUP,
	RIGHTDOWN,
	LEFTUP,
	LEFTDOWN,
	FREE,

};

enum class MYHOUSE_TILE {

	BAD_BOTTOM,
	GIFT,
	TV,
	HITTER,
	TABLE,
	CHAIR,
	MOVE_FARM = 28,
	BLOCK = 29,

};


enum class FOREST_TILE {

	MOVE_FARM = 28,
};

enum class TILE_LIST {

	MAPLE_TREE = 0,
	FINE_TREE,
	OAK_TREE,
	MAHOGANI_TREE,
	SMALL_STONE,
	BIG_STONE,
	SMALL_WOOD1,
	SMAA_WOOD2,
	MIDDLE_WOOD,
	BIG_WOOD,
	WEED1,
	WEED2,
	MY_HOUSE,
	PIERRE, 
	LEWIS,
	PENNY,
	ABIGAIL = 17,
	GUS=19,
	MOVE_SALOON,
	SHIPPING_BOX = 21,
	SHOP_FLAG = 22,
	MOVE_SHOP = 23,
	MOVE_FOREST = 24,
	MOVE_TOWN = 25,
	MOVE_BUSSTOP = 26,
	MOVE_HOUSE = 27,
	MOVE_FARM = 28,
	BLOCK = 29,

	STONE0 = 36,
	STONE1,
	STONE2,
	STONE3,
	STONE4,
	STONE5,

	COPPER,
	RUBY,
	AMETHYST,
	AQUAMARINE,

	MINE_FLOOR = 46,
	MOVE_MINE=48,

	BUG = 60,
	BAT,
	CRAB,
	GOLEM


};

enum class NPC_MOVE_FLAG
{
	PENNY_UP, PENNY_RIGHT, PENNY_DOWN, PENNY_LEFT, PENNY_WAIT, PENNY_OFF,

	LEWIS_UP = 18, LEWIS_RIGHT, LEWIS_DOWN, LEWIS_LEFT, LEWIS_WAIT, LEWIS_OFF,

	ABIGAIL_UP = 24, ABIGAIL_RIGHT, ABIGAIL_DOWN, ABIGAIL_LEFT, ABIGAIL_WAIT, ABIGAIL_OFF


};



enum class TILE_DIRT {
	BASIC,			LEFT_TOP,		MIDDLE_TOP,		RIGHT_TOP,			BASIC_WET, LEFT_TOP_WET, MIDDLE_TOP_WET, RIGHT_TOP_WET,
	H_LINE_TOP,		LEFT_MIDDLE,	MIDDLE_MIDDLE,	RIGHT_MIDDLE,		H_LINE_TOP_WET, LEFT_MIDDLE_WET, MIDDLE_MIDDLE_WET, RIGHT_MIDDLE_WET,
	H_LINE_MIDDLE,	LEFT_BOTTOM,	MIDDLE_BOTTOM,	RIGHT_BOTTOM,		H_LINE_MIDDLE_WET, LEFT_BOTTOM_WET, MIDDLE_BOTTOM_WET, RIGHT_BOTTOM_WET,
	H_LINE_BOTTOM,	W_LINE_LEFT,	W_LINE_MIDDLE,	W_LINE_RIGHT,		H_LINE_BOTTOM_WET, W_LINE_LEFT_WET, W_LINE_MIDDLE_WET, W_LINE_RIGHT_WET
};