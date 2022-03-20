#pragma once

#include "Scene.h"

class SceneTitle : public Scene
{
private:
	int timer;

public:
	void init();
	void update();
	void render();

};
