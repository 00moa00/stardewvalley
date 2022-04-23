#pragma once

enum class PLAYER
{
	//------< �⺻ �ȱ� >------------------------------------------------------------------
	RIGHT_WALK0, RIGHT_WALK1,RIGHT_WALK2, RIGHT_WALK3, RIGHT_INIT, RIGHT_WALK5,
	LEFT_WALK0, LEFT_WALK1, LEFT_WALK2, LEFT_WALK3, LEFT_INIT, LEFT_WALK5,
	FRONT_WALK0, FRONT_WALK1, FRONT_WALK2, FRONT_WALK3, FRONT_INIT, BACK_INIT,
	BACK_WALK0 = 24, BACK_WALK1, BACK_WALK2, BACK_WALK3, BACK_WALK4,


	//------< �� ��½ >------------------------------------------------------------------

	RIGHT_WALK_HAND0 = 36, RIGHT_WALK_HAND1, RIGHT_WALK_HAND2, RIGHT_WALK_HAND3, RIGHT_HAND_INIT, RIGHT_WALK_HAND5,

	LEFT_WALK_HAND0, LEFT_WALK_HAND1, LEFT_WALK_HAND2, LEFT_WALK_HAND3, LEFT_HAND_INIT, LEFT_WALK_HAND5,

	FRONT_WALK_HAND0, FRONT_WALK_HAND1, FRONT_WALK_HAND2, FRONT_WALK_HAND3, FRONT_HAND_INIT, BACK_HAND_INIT,

	BACK_WALK_HAND0 =60 , BACK_WALK_HAND1, BACK_WALK_HAND2, BACK_WALK_HAND3, BACK_WALK_HAND4,



	//------< ���Ѹ��� >------------------------------------------------------------------

	WATER_RIGHT0 = 72, WATER_RIGHT1, WATER_RIGHT2,
	WATER_LEFT0 = 78, WATER_LEFT1, WATER_LEFT2,

	WATER_FRONT0 = 84, WATER_FRONT1, WATER_FRONT2,
	WATER_BACK0 = 96, WATER_BACK1, WATER_BACK2,

	//------< ȣ�� >------------------------------------------------------------------

	HOE_RIGHT0 = 120, HOE_RIGHT1, HOE_RIGHT2, HOE_RIGHT3, HOE_RIGHT4,
	HOE_LEFT0 = 126, HOE_LEFT1, HOE_LEFT2, HOE_LEFT3, HOE_LEFT4,

	HOE_RIGHT_HOLD0 = 132, HOE_RIGHT_HOLD1, HOE_RIGHT_HOLD2, HOE_RIGHT_FREE0 = 136, HOE_RIGHT_FREE1,
	HOE_LEFT_HOLD0 = 138, HOE_LEFT_HOLD1, HOE_LEFT_HOLD2, HOE_LEFT_FREE0 = 142, HOE_LEFT_FREE1,

	HOE_FRONT0 = 144, HOE_FRONT1, HOE_FRONT2, HOE_FRONT3, HOE_FRONT4, HOE_FRONT5,
	HOE_FRONT_HOLD0 = 156, HOE_FRONT_HOLD1, HOE_FRONT_HOLD2, HOE_FRONT_FREE0, HOE_FRONT_FREE1, HOE_FRONT_FREE2,

	HOE_BACK0 = 168, HOE_BACK1, HOE_BACK2,
	HOE_BACK_HOLD0 = 180, HOE_BACK_HOLD1, HOE_BACK_HOLD2, HOE_BACK_FREE0, HOE_BACK_FREE1,


};






enum class HOE_RIGHT
{
	HOE_RIGHT0, HOE_RIGHT1, HOE_RIGHT2, HOE_RIGHT3, HOE_RIGHT4,
};

enum class HOE_LEFT
{
	HOE_LEFT0, HOE_LEFT1, HOE_LEFT2, HOE_LEFT3, HOE_LEFT4,
};

enum class HOE_FRONT
{
	HOE_FRONT0, HOE_FRONT1, HOE_FRONT2, HOE_FRONT3, HOE_FRONT4,
};
enum class HOE_BACK
{
	HOE_BACK0, HOE_BACK1, HOE_BACK2
};


enum class AXE_RIGHT
{
	AXE_RIGHT0, AXE_RIGHT1, AXE_RIGHT2, AXE_RIGHT3, AXE_RIGHT4,
};

enum class AXE_LEFT
{
	AXE_LEFT0, AXE_LEFT1, AXE_LEFT2, AXE_LEFT3, AXE_LEFT4,
};

enum class  AXE_FRONT
{
	AXE_FRONT0, AXE_FRONT1, AXE_FRONT2, AXE_FRONT3, AXE_FRONT4,
};

enum class AXE_BACK
{
	AXE_BACK0, AXE_BACK1, AXE_BACK2
};





enum class PICKAXE_RIGHT
{
	PICKAXE_RIGHT0, PICKAXE_RIGHT1, PICKAXE_RIGHT2, PICKAXE_RIGHT3, PICKAXE_RIGHT4,
};

enum class PICKAXE_LEFT
{
	PICKAXE_LEFT0, PICKAXE_LEFT1, PICKAXE_LEFT2, PICKAXE_LEFT3, PICKAXE_LEFT4,
};

enum class PICKAXE_FRONT
{
	PICKAXE_FRONT0, PICKAXE_FRONT1, PICKAXE_FRONT2, PICKAXE_FRONT3, PICKAXE_FRONT4,
};


enum class PICKAXE_BACK
{
	PICKAXE_BACK0, PICKAXE_BACK1, PICKAXE_BACK2
};




enum class WATERINGCAN_RIGHT
{
	WATERINGCAN_RIGHT0, WATERINGCAN_RIGHT1, WATERINGCAN_RIGHT2
};


enum class WATERINGCAN_LEFT
{
	WATERINGCAN_LEFT0, WATERINGCAN_LEFT1, WATERINGCAN_LEFT2
};

enum class WATERINGCAN_FRONT
{
	WATERINGCAN_FRONT0, WATERINGCAN_FRONT1, WATERINGCAN_FRONT2
};


enum class WATERINGCAN_BACK
{
	WATERINGCAN_BACK0, WATERINGCAN_BACK1, WATERINGCAN_BACK2
};
