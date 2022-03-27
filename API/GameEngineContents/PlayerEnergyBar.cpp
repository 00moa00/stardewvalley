#include "PlayerEnergyBar.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngineBase/GameEngineTime.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

PlayerEnergyBar::PlayerEnergyBar()
	:
	PlayerEngergyBar_(nullptr),
	ImageScale_({ 0.f , 0.f })
{
}

PlayerEnergyBar::~PlayerEnergyBar()
{
}



void PlayerEnergyBar::Start()
{
	ImageScale_ = { 1.8f, 1.8f };
	EnergyBar_ = { 6.f * ImageScale_.x, 42.f * ImageScale_.y };

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