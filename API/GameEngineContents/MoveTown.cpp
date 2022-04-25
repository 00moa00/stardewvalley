#include "MoveTown.h"
MoveTown* MoveTown::MainMoveTown;

MoveTown::MoveTown() 
{
}

MoveTown::~MoveTown() 
{
}

void MoveTown::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");

	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	//SetScale({ 48.f, 48.f });
	ItemCollider_ = CreateCollision("MoveTown", { 48, 48 });
	ItemType_ = ITEMTYPE::FALG;

}

void MoveTown::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MoveTown = this;
}

