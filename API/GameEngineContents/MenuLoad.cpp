#include "MenuLoad.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "TitleLevel.h"


MenuLoad::MenuLoad()
	:	
		Load_(nullptr),
		NewGameCollision_(nullptr)
{
}

MenuLoad::~MenuLoad()
{
}


void MenuLoad::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y + 250.f });

	Load_ = CreateRenderer("TitleMenuButtons.bmp");
	Load_->SetIndex(1);

	NewGameCollision_ = CreateCollision("MenuLoad", { 222,174 });

}

void MenuLoad::Render()
{

}

void MenuLoad::Update()
{

	if (isMouseOver() == true) 
	{
		Load_->SetIndex(1+4);
	} 
	else 
	{
		Load_->SetIndex(1);

	}

}
