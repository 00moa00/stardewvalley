#include "Pickaxe.h"

Pickaxe::Pickaxe() 
{
}

Pickaxe::~Pickaxe() 
{
}

void Pickaxe::Start()
{
	ItemRenderer_ = CreateRenderer("tools.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(TOOL::PICKAXE_IN_INVENTROY));
	ItemRenderer_->CameraEffectOff();

	///ItemRenderer_->SetPivot()
	ItemCollider_ = CreateCollision("Item", { 40, 40 });
	
	ItemType_ = ITEMTYPE::TOOL;
	ToolType_ = TOOLTYPE::PICKAXE;

	SetItemName("Pickaxe");

}

void Pickaxe::Update()
{
}

