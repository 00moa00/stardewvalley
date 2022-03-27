#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h>

#include "MenuNewGame.h"
#include "MenuLoad.h"
#include "MenuExit.h"

GameEngineLevel* MenuNewGame_ = nullptr;
GameEngineLevel* MenuLoad_ = nullptr;
GameEngineLevel* MenuExit_ = nullptr;


TitleLogo::TitleLogo()
	:	Speed_(50.0f),
		Logo_(nullptr)
{
}

TitleLogo::~TitleLogo() 
{
}



void TitleLogo::Start() 
{
	SetPosition({ GameEngineWindow::GetScale().Half().x,0 });


	GameEngineRenderer* Logo_;


	Logo_ = CreateRenderer("TitleButtons.ko-KR.bmp");
	Logo_->SetScale({ 420, 207 }); 	//400, 187  로고 원본 크기
	Logo_->SetIndex(0);


}

void TitleLogo::Render() 
{
	//DebugRectRender();

}

void TitleLogo::Update()
{
	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * (Speed_ ));

	if (GetPosition().y >= GameEngineWindow::GetScale().Half().y - 100.f) {
		Speed_ = 0.0f;

	}

	
}
