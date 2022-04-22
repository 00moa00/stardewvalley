#include "PlayerEnergyFrame.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngineBase/GameEngineTime.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

PlayerEnergyFrame::PlayerEnergyFrame() 
	:	PlayerEngergyFrame_(nullptr)

{
}

PlayerEnergyFrame::~PlayerEnergyFrame() 
{
}



void PlayerEnergyFrame::Start()
{
	//SetPosition({GameEngineWindow::GetScale().x - 12.f ,GameEngineWindow::GetScale().y - 56.f });
	//12 56
	//PlayerEngergyFrame_ = CreateRenderer("UIEnergy.bmp");
	//PlayerEngergyFrame_->CameraEffectOff();


}

void PlayerEnergyFrame::Update()
{


}

void PlayerEnergyFrame::Render()
{


}