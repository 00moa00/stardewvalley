#include "Swoard.h"
Swoard* Swoard::MainSwoard = nullptr;

Swoard::Swoard() 
{
}

Swoard::~Swoard() 
{
}

void Swoard::Start()
{
	ItemRenderer_ = CreateRenderer("weapons.bmp");
	ItemRenderer_->SetIndex(0);
	ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivot({ 0, -24 });

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	ItemType_ = ITEMTYPE::TOOL;
	ToolType_ = TOOLTYPE::SWOARD;

	ItemName_ = "Swoard";

	FileName_ = "weapons.bmp";
	FileIndex_ = 0;
}

void Swoard::Update()
{
}

void Swoard::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainSwoard = this;

}
