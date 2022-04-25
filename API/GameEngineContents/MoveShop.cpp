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
	ItemType_ = ITEMTYPE::FALG;

}

void MoveShop::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MoveShop = this;
}

