#include "Pickaxe.h"

Pickaxe* Pickaxe::MainPickaxe = nullptr;

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

	ItemCollider_ = CreateCollision("Item", { 40, 40 });
	
	ItemType_ = ITEMTYPE::TOOL;
	ToolType_ = TOOLTYPE::PICKAXE;

	Name_ = "Pickaxe";

	FileName_ = "tools.bmp";
	FileIndex_ = static_cast<size_t>(TOOL::PICKAXE_IN_INVENTROY);

}

void Pickaxe::Update()
{
}

void Pickaxe::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPickaxe = this;
}

