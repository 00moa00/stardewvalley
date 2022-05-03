#include "PlayerEnergyFrame.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> 

#include "RendererData.h"

PlayerEnergyFrame* PlayerEnergyFrame::MainPlayerEnergyFrame = nullptr;
PlayerEnergyBar* PlayerEnergyFrame::MainPlayerEnergyBar = nullptr;

PlayerEnergyFrame::PlayerEnergyFrame() 
	:	
	PlayerEngergyFrame_(nullptr)
{
}

PlayerEnergyFrame::~PlayerEnergyFrame() 
{
}

void PlayerEnergyFrame::Start()
{
	SetPosition({ GameEngineWindow::GetScale().x - 50.f, GameEngineWindow::GetScale().y - 100.f });

	PlayerEngergyFrame_ = CreateRenderer("UIEnergy.bmp");
	PlayerEngergyFrame_->CameraEffectOff();

	MainPlayerEnergyBar = GetLevel()->CreateActor<PlayerEnergyBar>(static_cast<int>(PLAYLEVEL::ENERGYBAR));
	MainPlayerEnergyBar->SetPosition({ this->GetPosition().x, this->GetPosition().y + (126.f/2) + 35.f / 2});
}

void PlayerEnergyFrame::Update()
{


}

void PlayerEnergyFrame::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayerEnergyFrame = this;
	MainPlayerEnergyBar = MainPlayerEnergyBar;
}

void PlayerEnergyFrame::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	MainPlayerEnergyBar->NextLevelOn();
}

