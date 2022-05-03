#include "PlayerHPFrame.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> 
#include "RendererData.h"

PlayerHPFrame* PlayerHPFrame::MainPlayerHPFrame = nullptr;
PlayerEnergyBar* PlayerHPFrame::MainPlayerHPBar = nullptr;

PlayerHPFrame::PlayerHPFrame() 
	:
	PlayerEngergyFrame_(nullptr)
{
}

PlayerHPFrame::~PlayerHPFrame() 
{
}

void PlayerHPFrame::Start()
{
	SetPosition({ GameEngineWindow::GetScale().x - 85.f, GameEngineWindow::GetScale().y - 100.f });

	PlayerEngergyFrame_ = CreateRenderer("UIHP.bmp");
	PlayerEngergyFrame_->CameraEffectOff();

	MainPlayerHPBar = GetLevel()->CreateActor<PlayerEnergyBar>(static_cast<int>(PLAYLEVEL::ENERGYBAR));
	MainPlayerHPBar->SetPosition({ this->GetPosition().x, this->GetPosition().y + (126.f / 2) + 35.f / 2 });
}

void PlayerHPFrame::Update()
{
}

void PlayerHPFrame::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayerHPFrame = this;
	MainPlayerHPBar = MainPlayerHPBar;
}

void PlayerHPFrame::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	MainPlayerHPBar->NextLevelOn();

}
