#include "MenuExit.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "TitleLevel.h"


MenuExit::MenuExit()
	:	
	MenuExit_(nullptr)
{
}

MenuExit::~MenuExit()
{
}


void MenuExit::Start()
{
	SetPosition( { GameEngineWindow::GetScale().Half().x + 250.f , GameEngineWindow::GetScale().Half().y + 250.f });


	MenuExit_ = CreateRenderer("TitleMenuButtons.bmp");
	MenuExit_->SetIndex(3);

	NewGameCollision_ = CreateCollision("MenuExit", {222,174});
}

void MenuExit::Render()
{

}

void MenuExit::Update()
{
	if (isMouseOver() == true)
	{
		MenuExit_->SetIndex(3 + 4);
	}
	else 
	{
		MenuExit_->SetIndex(3 );

	}

}
