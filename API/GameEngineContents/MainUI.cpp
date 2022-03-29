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
	SetPosition({ GameEngineWindow::GetScale().x - 140.f/1.5f,  114.f/1.5f});

	MainUI_ = CreateRenderer("UITop.bmp");
	//PlayerEngergyBar_->SetScale({ EnergyBar_.x,   EnergyBar_.y });

}

void MainUI::Update()
{
}

void MainUI::Render()
{
}
