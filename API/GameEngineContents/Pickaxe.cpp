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
	ItemRenderer_->SetPivot({ 0, 24 });
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });
	
	ObjectType_ = OBJECTTYPE::TOOL;
	ToolType_ = TOOLTYPE::PICKAXE;

	ItemName_ = "Pickaxe";

	FileName_ = "tools.bmp";
	FileIndex_ = static_cast<size_t>(TOOL::PICKAXE_IN_INVENTROY);

	Power_ = 1;

}

void Pickaxe::Update()
{
}

void Pickaxe::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPickaxe = this;
}

