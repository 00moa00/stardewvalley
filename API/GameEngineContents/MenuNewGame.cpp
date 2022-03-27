#include "MenuNewGame.h"

#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "TitleLevel.h"


MenuNewGame::MenuNewGame()
	:	NewGame_(nullptr),
		isClick_(false)
{
}

MenuNewGame::~MenuNewGame() 
{
}


void MenuNewGame::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x - 174.f,GameEngineWindow::GetScale().Half().y + 150.f});

	NewGame_ = CreateRenderer("TitleButtons.ko-KR.bmp");
	NewGame_->SetIndex(static_cast<size_t>(MENU::MenuNewGame));
}

void MenuNewGame::Render()
{
	//DebugRectRender();

}

void MenuNewGame::Update()
{
	if (GetIsClick() == true) {
		NewGame_->SetIndex(static_cast<size_t>(MENU::ClickMenuNewGame));
	} else {
		NewGame_->SetIndex(static_cast<size_t>(MENU::MenuNewGame));
	}
}
