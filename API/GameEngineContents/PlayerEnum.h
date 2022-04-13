#pragma once

enum PLAYER
{
	RIGHT_WALK0, RIGHT_WALK1,RIGHT_WALK2, RIGHT_WALK3, RIGHT_INIT, RIGHT_WALK5,
	LEFT_WALK0, LEFT_WALK1, LEFT_WALK2, LEFT_WALK3, LEFT_INIT, LEFT_WALK5,
	FRONT_WALK0, FRONT_WALK1, FRONT_WALK2, FRONT_WALK3, FRONT_INIT, BACK_INIT,
	BACK_WALK0 = 24, BACK_WALK1, BACK_WALK2, BACK_WALK3, BACK_WALK4,


	HOE_RIGHT0= 120, HOE_RIGHT1, HOE_RIGHT2, HOE_RIGHT3, HOE_RIGHT4,
	HOE_LEFT0 = 126, HOE_LEFT1, HOE_LEFT2, HOE_LEFT3, HOE_LEFT4,


	HOE_RIGHT_HOLD0 = 132, HOE_RIGHT_HOLD1, HOE_RIGHT_HOLD2, HOE_RIGHT_FREE0 = 136, HOE_RIGHT_FREE1,
	HOE_LEFT_HOLD0 = 138, HOE_LEFT_HOLD1, HOE_LEFT_HOLD2, HOE_LEFT_FREE0 = 142, HOE_LEFT_FREE1,

	HOE_FRONT0 = 144 , HOE_FRONT1, HOE_FRONT2, HOE_FRONT3, HOE_FRONT4, HOE_FRONT5,
	HOE_FRONT_HOLD0 = 156, HOE_FRONT_HOLD1, HOE_FRONT_HOLD2, HOE_FRONT_FREE0, HOE_FRONT_FREE1, HOE_FRONT_FREE2,

	HOE_BACK0 = 168, HOE_BACK1, HOE_BACK2, 
	HOE_BACK_HOLD0 = 180, HOE_BACK_HOLD1, HOE_BACK_HOLD2, HOE_BACK_FREE0, HOE_BACK_FREE1,


};