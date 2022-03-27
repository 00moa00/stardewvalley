#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

TitleBackGround::TitleBackGround() 
{
	// Level_ = nullptr;
}

TitleBackGround::~TitleBackGround() 
{
}

void TitleBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());


	CreateRenderer("titleback.bmp");



	//Render->SetIndex(10);

}

void TitleBackGround::Render() 
{

}