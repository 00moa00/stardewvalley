#include "MainUI.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>


#include <GameEngine/GameEngineLevel.h> 

MainUI::MainUI() 
{
}

MainUI::~MainUI() 
{
}

void MainUI::Start()
{
	SetPosition({ GameEngineWindow::GetScale().x - (140.f/1.5f) - 50.f,  (114.f/1.5f) + 50.f});

	MainUI_ = CreateRenderer("UITop.bmp");
	//PlayerEngergyBar_->SetScale({ EnergyBar_.x,   EnergyBar_.y });

	MainUI_->CameraEffectOff();
}

void MainUI::Update()
{
}

void MainUI::Render()
{
}
