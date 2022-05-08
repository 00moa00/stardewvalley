#include "Watering_Can.h"

Watering_Can* Watering_Can::MainWateringCan = nullptr;

Watering_Can::Watering_Can() 
{
}

Watering_Can::~Watering_Can() 
{
}

void Watering_Can::Start()
{
	//Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	//Font_->ChangeNumItem(1);

	ItemRenderer_ = CreateRenderer("tools.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(TOOL::WATER_RIGHT00));
	//ItemRenderer_->SetPivot({ 0, 24 });
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });
	
	ObjectType_ = OBJECTTYPE::TOOL;
	ToolType_ = TOOLTYPE::WATTERING_CAN;

	ItemName_ = "Watering_Can";

	FileName_ = "tools.bmp";
	FileIndex_ = static_cast<size_t>(TOOL::WATER_RIGHT00);

}

void Watering_Can::Update()
{
}

void Watering_Can::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainWateringCan = this;
}

