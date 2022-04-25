#include "MoveFarm.h"
MoveFarm* MoveFarm::MainMoveFarm;

MoveFarm::MoveFarm()
{
}

MoveFarm::~MoveFarm() 
{
}

void MoveFarm::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");
	
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	//SetScale({ 48.f, 48.f });
	ItemCollider_ = CreateCollision("MoveFarm", { 48, 48 });
	ItemType_ = ITEMTYPE::FALG;
}

void MoveFarm::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMoveFarm = this;
}

