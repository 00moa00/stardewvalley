#include "PlayerBackGround.h"


#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h>

PlayerBackGround::PlayerBackGround() 
	:
	PlayerBackGround_(nullptr)
{
}

PlayerBackGround::~PlayerBackGround() 
{
}

void PlayerBackGround::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 120.f});
	PlayerBackGround_ = CreateRenderer("daybg.bmp");
	PlayerBackGround_->SetScale({ 256.f * 0.3f, 384.f * 0.3f });

}

void PlayerBackGround::Update()
{

}

void PlayerBackGround::Render()
{
}
