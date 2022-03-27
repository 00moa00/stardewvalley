#include "PlayerEnergyFrame.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngineBase/GameEngineTime.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

PlayerEnergyFrame::PlayerEnergyFrame() 
	:	PlayerEngergyFrame_(nullptr),
		ImageScale_({ 0.f , 0.f})

{
}

PlayerEnergyFrame::~PlayerEnergyFrame() 
{
}



void PlayerEnergyFrame::Start()
{
	ImageScale_ = { 1.8f ,1.8f };
	SetPosition({GameEngineWindow::GetScale().x - 6.f * ImageScale_.x,GameEngineWindow::GetScale().y - 28.f * ImageScale_.y });
	//12 56
	PlayerEngergyFrame_ = CreateRenderer("UIEnergy.bmp");
	PlayerEngergyFrame_->SetScale({ 12.f * ImageScale_.x, 56.f * ImageScale_.y });


}

void PlayerEnergyFrame::Update()
{


}

void PlayerEnergyFrame::Render()
{


}