#include "MenuExit.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "TitleLevel.h"


MenuExit::MenuExit()
	:	MenuExit_(nullptr)
{
}

MenuExit::~MenuExit()
{
}


void MenuExit::Start()
{
	SetPosition( { GameEngineWindow::GetScale().Half().x + 87.f , GameEngineWindow::GetScale().Half().y + 50.f });


	MenuExit_ = CreateRenderer("TitleButtons.ko-KR.bmp");
	MenuExit_->SetIndex(static_cast<size_t>(MENU::MenuExit));

}

void MenuExit::Render()
{

}

void MenuExit::Update()
{
	if (GetIsClick() == true) {
		MenuExit_->SetIndex(static_cast<size_t>(MENU::ClickMenuExit));
	}
	else {
		MenuExit_->SetIndex(static_cast<size_t>(MENU::MenuExit));

	}

}
