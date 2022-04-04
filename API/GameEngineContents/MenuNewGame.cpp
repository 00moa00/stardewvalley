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
	:	NewGame_(nullptr),
		isMouseOver_(false),
		NewGameCollision_(nullptr)
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

	NewGameCollision_ = CreateCollision("NewGame", { 148, 116 });

}

void MenuNewGame::Render()
{
	//DebugRectRender();

}

void MenuNewGame::Update()
{
	if (isMouseOver_) NewGame_->SetIndex(static_cast<size_t>(MENU::ClickMenuNewGame));
	else NewGame_->SetIndex(static_cast<size_t>(MENU::MenuNewGame));

	MouseEvent();

}


void MenuNewGame::MouseEvent()
{

	if (MouseOver()&& (true == GameEngineInput::GetInst()->IsDown("LeftClick"))) GameEngine::GetInst().ChangeLevel("Play");
	
	if (MouseOver()) isMouseOver_ = true;

}

bool MenuNewGame::MouseOver()
{
	std::vector<GameEngineCollision*> ColList;

	return (NewGameCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}
