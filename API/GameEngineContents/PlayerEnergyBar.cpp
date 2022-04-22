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
	EnergyBar_ = { 12.f , 84.f  };

	//SetPosition({ GameEngineWindow::GetScale().x - EnergyBar_.x, GameEngineWindow::GetScale().y - EnergyBar_.y/2 });

	//PlayerEngergyBar_ = CreateRenderer("HPUIBar.bmp");
	//PlayerEngergyBar_->CameraEffectOff();
	//PlayerEngergyBar_->SetScale({ EnergyBar_.x,   EnergyBar_.y });

	//CreateRenderer("HPUIBar.bmp", RenderPivot::BOT);


}

void PlayerEnergyBar::Update()
{

	//PlayerEngergyBar_->SetScale({ EnergyBar_.x,   EnergyBar_.y });

}

void PlayerEnergyBar::Render()
{


}