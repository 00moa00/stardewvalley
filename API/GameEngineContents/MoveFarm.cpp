#include "MoveFarm.h"
MoveFarm* MoveFarm::MainMoveFarm = nullptr;

MoveFarm::MoveFarm()
{
}

MoveFarm::~MoveFarm() 
{
}

void MoveFarm::Start()
{
	ItemRenderer_ = CreateRenderer("Empty.bmp");
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);

	ItemCollider_ = CreateCollision("MoveFarm", { 48, 48 });

	ItemType_ = ITEMTYPE::FALG;
}

void MoveFarm::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMoveFarm = this;
}

