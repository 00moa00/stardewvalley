#include "Axe.h"

Axe* Axe::MainAxe = nullptr;

Axe::Axe() 
{
}

Axe::~Axe() 
{
}

void Axe::Start()
{
	ItemRenderer_ = CreateRenderer("tools.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(TOOL::AXE_IN_INVENTROY));
	//ItemRenderer_->SetPivot({0, 24});
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	ObjectType_ = OBJECTTYPE::TOOL;
	ToolType_ = TOOLTYPE::AXE;

	ItemName_ = "Axe";

	FileName_ = "tools.bmp";
	FileIndex_ = static_cast<size_t>(TOOL::AXE_IN_INVENTROY);

	Power_ = 1;

}

void Axe::Update()
{
}

void Axe::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainAxe = this;
}


