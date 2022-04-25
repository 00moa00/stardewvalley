#include "MoveHouse.h"
MoveHouse* MoveHouse::MainMoveHouse;

MoveHouse::MoveHouse() 
{
}

MoveHouse::~MoveHouse() 
{
}

void MoveHouse::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	ItemCollider_ = CreateCollision("MoveHouse", { 48, 48 });
	ItemType_ = ITEMTYPE::FALG;
}

void MoveHouse::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMoveHouse = this;
}

