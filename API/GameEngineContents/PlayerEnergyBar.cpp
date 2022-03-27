#include "PlayerEnergyBar.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngineBase/GameEngineTime.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

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

	SetPosition({ GameEngineWindow::GetScale().x - EnergyBar_.x, GameEngineWindow::GetScale().y - EnergyBar_.y/2 });

	PlayerEngergyBar_ = CreateRenderer("HPUIBar.bmp");
	//PlayerEngergyBar_->SetScale({ EnergyBar_.x,   EnergyBar_.y });

	//CreateRenderer("HPUIBar.bmp", RenderPivot::BOT);


}

void PlayerEnergyBar::Update()
{

	PlayerEngergyBar_->SetScale({ EnergyBar_.x,   EnergyBar_.y });

}

void PlayerEnergyBar::Render()
{


}