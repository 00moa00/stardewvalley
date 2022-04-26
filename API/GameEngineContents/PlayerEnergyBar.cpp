#include "PlayerEnergyBar.h"


#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>


#include <GameEngine/GameEngineLevel.h> 


PlayerEnergyBar::PlayerEnergyBar()
	:
	PlayerEngergyBar_(nullptr)
{
}

PlayerEnergyBar::~PlayerEnergyBar()
{
}



void PlayerEnergyBar::Start()
{
	PlayerEngergyBar_ = CreateRenderer("HPUIBar.bmp");
	PlayerEngergyBar_->CameraEffectOff();
	PlayerEngergyBar_->SetScale({ 18, 126 });
	PlayerEngergyBar_->SetPivotType(RenderPivot::BOT);
}

void PlayerEnergyBar::Update()
{

}

void PlayerEnergyBar::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void PlayerEnergyBar::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

