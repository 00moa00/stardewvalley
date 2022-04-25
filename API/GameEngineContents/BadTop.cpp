#include "BadTop.h"

BadTop::BadTop() 
{
}

BadTop::~BadTop() 
{
}

void BadTop::Start()
{
	ItemRenderer_ = CreateRenderer("Bad.bmp");
	ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::BOT);
	ItemRenderer_->SetPivot({ GetPosition().x , GetPosition().y - 24.f });
	ItemType_ = ITEMTYPE::TOOL;
}

void BadTop::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void BadTop::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

