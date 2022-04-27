#include "MenuNewGame.h"

#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>

#include "TitleLevel.h"


MenuNewGame::MenuNewGame()
	:	
	isMouseOver_(false),
	CustomBoardOpen_(false),
	NewGame_(nullptr),
	NewGameCollision_(nullptr)
{
}

MenuNewGame::~MenuNewGame() 
{
}


void MenuNewGame::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x - 250.f,GameEngineWindow::GetScale().Half().y + 250.f});

	NewGame_ = CreateRenderer("TitleMenuButtons.bmp");
	NewGame_->SetIndex(0);

	NewGameCollision_ = CreateCollision("NewGame", { 222,174 });

}

void MenuNewGame::Render()
{
	//DebugRectRender();

}

void MenuNewGame::Update()
{
	if (isMouseOver() == true)
	{
		NewGame_->SetIndex(0 + 4);
	}
	else
	{
		NewGame_->SetIndex(0);
	}

	if (isMouseOver() == true && true == GameEngineInput::GetInst()->IsDown("LeftClick"))
	{
		//GameEngine::GetInst().ChangeLevel("MyHouseLevel");
		CustomBoardOpen_ = true;
	}

}

