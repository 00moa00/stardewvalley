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

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	ObjectType_ = OBJECTTYPE::TOOL;
	ToolType_ = TOOLTYPE::SWOARD;

	ItemName_ = "Swoard";

	FileName_ = "weapons.bmp";
	FileIndex_ = 0;

	Power_ = 5;
}

void Swoard::Update()
{
}

void Swoard::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainSwoard = this;

}
