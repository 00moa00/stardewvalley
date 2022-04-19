#include "MoveForest.h"

MoveForest::MoveForest() 
{
}

MoveForest::~MoveForest() 
{
}

void MoveForest::Start()
{

	ItemRenderer_ = CreateRenderer("block.bmp");
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	//SetScale({ 48.f, 48.f });
	ItemCollider_ = CreateCollision("MoveForest", { 48, 48 });
	ItemType_ = ITEMTYPE::FALG;
}

