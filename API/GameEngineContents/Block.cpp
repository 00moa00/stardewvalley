#include "Block.h"

Block::Block() 
{
}

Block::~Block() 
{
}

void Block::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");
	//ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WILD_HORSERADISH));
	//ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::BOT);
	SetScale({ 48.f, 48.f });
	ItemCollider_ = CreateCollision("Object", { 48, 48 });
	ItemType_ = ITEMTYPE::FALG;
}

