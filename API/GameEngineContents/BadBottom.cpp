#include "BadBottom.h"

BadBottom* BadBottom::MainBadBottom = nullptr;


BadBottom::BadBottom() 
{
}

BadBottom::~BadBottom() 
{
}

void BadBottom::Start()
{
	ItemRenderer_ = CreateRenderer("BadBottom.bmp");
	ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::BOT);
	ItemRenderer_->SetPivot({ GetPosition().x , GetPosition().y - 24.f });
	
	SetScale({ 96, 30 });

	ObjectType_ = OBJECTTYPE::TOOL;
}

void BadBottom::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainBadBottom = this;
}

void BadBottom::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

