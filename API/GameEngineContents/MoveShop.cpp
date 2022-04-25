#include "MoveShop.h"
MoveShop* MoveShop::MainMoveShop;

MoveShop::MoveShop() 
{
}

MoveShop::~MoveShop() 
{
}

void MoveShop::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");

	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	ItemCollider_ = CreateCollision("MoveShop", { 48, 48 });
	ItemType_ = ITEMTYPE::FLAG;

}

void MoveShop::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMoveShop = this;
}

