#pragma once
#include "Obj2d.h"
#include "Singleton.h"

class Player : public OBJ2D, public Singleton<Player>
{
private:
	//static const int	OBJ_MAX = 1;
	//OBJ2D				obj[OBJ_MAX];

public:
	//OBJ2D* begin()	{ return &obj[0]; }
	//OBJ2D* end()	{ return &obj[OBJ_MAX]; }
	void init();
	void update();
};