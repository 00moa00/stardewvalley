#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngine/GameEngineLevel.h>

#include "MenuNewGame.h"
#include "MenuLoad.h"
#include "MenuExit.h"

GameEngineLevel* MenuNewGame_ = nullptr;
GameEngineLevel* MenuLoad_ = nullptr;
GameEngineLevel* MenuExit_ = nullptr;


TitleLogo::TitleLogo()
	:	Speed_(50.0f),
		Logo_(nullptr),
		ScaleSpeed_({0.0f,0.0f})
{
}

TitleLogo::~TitleLogo() 
{
}



void TitleLogo::Start() 
{
	SetPosition({ GameEngineWindow::GetScale().Half().x, 0 });

	Logo_ = CreateRenderer("logo.bmp");
	//Logo_->SetIndex(0);
	Logo_->SetScale({ 600, 330 }); 	//800, 440  로고 원본 크기

}

void TitleLogo::Render() 
{
}

void TitleLogo::Update()
{
	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * (Speed_ ));

	if (GetPosition().y >= GameEngineWindow::GetScale().Half().y - 100.f) {
		Speed_ = 0.0f;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Enter")) {

		SetPosition({ GameEngineWindow::GetScale().Half().x,GameEngineWindow::GetScale().Half().y - 100.f });

	}


	
}
