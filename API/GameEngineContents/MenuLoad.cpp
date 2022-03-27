#include "MenuLoad.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "TitleLevel.h"


MenuLoad::MenuLoad()
	:	MenuLoad_(nullptr)
{
}

MenuLoad::~MenuLoad()
{
}


void MenuLoad::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y + 150.f });


	MenuLoad_ = CreateRenderer("TitleButtons.ko-KR.bmp");
	MenuLoad_->SetIndex(static_cast<size_t>(MENU::MenuLoad));


}

void MenuLoad::Render()
{

}

void MenuLoad::Update()
{

	if (GetIsClick() == true) {
		MenuLoad_->SetIndex(static_cast<size_t>(MENU::ClickMenuLoad));
	} else {
		MenuLoad_->SetIndex(static_cast<size_t>(MENU::MenuLoad));

	}



}
