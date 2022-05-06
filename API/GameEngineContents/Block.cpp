#include "Block.h"

Block::Block() 
{
}

Block::~Block() 
{
}

void Block::Start()
{
	//ItemRenderer_ = CreateRenderer("block.bmp");
	//ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	SetScale({ 40, 48.f });
	ItemCollider_ = CreateCollision("MapObject", { 40, 47 });
	//ItemCollider_->SetPivot({0,-12});

	ObjectType_ = OBJECTTYPE::BLOCK;
}

