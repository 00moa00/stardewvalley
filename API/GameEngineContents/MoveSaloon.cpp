#include "MoveSaloon.h"
MoveSaloon* MoveSaloon::MainMoveSaloon;

MoveSaloon::MoveSaloon() 
{
}

MoveSaloon::~MoveSaloon() 
{
}

void MoveSaloon::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");

	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	ItemCollider_ = CreateCollision("MoveSalon", { 48, 48 });
	ItemType_ = ITEMTYPE::FLAG;
}

void MoveSaloon::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMoveSaloon = this;
}

