#include "Bird.h"

Bird::Bird() 
{
}

Bird::~Bird() 
{
}

void Bird::Start()
{
	Bird_ = CreateRenderer();
	Bird_->CreateAnimation("TitleBird.bmp", "BIRD", 0, 3, 0.120f, true);
	Bird_->ChangeAnimation("BIRD");
}

