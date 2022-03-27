#include "TitleLevel.h"

#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "TitleBackGround.h"




TitleLevel::TitleLevel() 
	:	TitleLogo_(nullptr),
		MenuExit_(nullptr),
		MenuLoad_(nullptr),
		MenuNewGame_(nullptr),
		isPopup_(false),
		Timer_(0),
	CurrentMenu_(KEYBOARD::Wait)
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading() 
{

	CreateActor<TitleBackGround>(0);
	TitleLogo_ = CreateActor<TitleLogo>(1);


	//if (false == GameEngineInput::GetInst()->IsKey("ArrowLeft"))
	//{
	//	GameEngineInput::GetInst()->CreateKey("ArrowLeft", VK_LEFT);
	//	GameEngineInput::GetInst()->CreateKey("Arrowright", VK_RIGHT);
	//	GameEngineInput::GetInst()->CreateKey("Enter", VK_RETURN);
	//	GameEngineInput::GetInst()->CreateKey("Esc", VK_ESCAPE);
	//}
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		// 이때 대문자여야 합니다.
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		//GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');

		// VK_LBUTTON;
	}
}

void TitleLevel::Update()
{
	//매뉴바 팝업

	if ((TitleLogo_->GetPosition().y > GameEngineWindow::GetScale().Half().y - 100.f)
		&& isPopup_ == false) {

		AddTimer(GameEngineTime::GetDeltaTime() + (int)1);

		if (getTimer() > 150 && MenuNewGame_ == nullptr) MenuNewGame_ = CreateActor<MenuNewGame>(2);
		if (getTimer() > 300 && MenuLoad_ == nullptr) MenuLoad_ = CreateActor<MenuLoad>(3);
		if (getTimer() > 450 && MenuExit_== nullptr) {
			MenuExit_ = CreateActor<MenuExit>(4);
			isPopup_ = true;
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveRight") && CurrentMenu_ < KEYBOARD::MAX) ++MoveMenu_;
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft") && CurrentMenu_ > KEYBOARD::Wait) --MoveMenu_;

	CurrentMenu_ = static_cast<KEYBOARD>(MoveMenu_);

	switch (CurrentMenu_)
	{

	case KEYBOARD::Wait:
		break;

	case KEYBOARD::MenuNewGame :
		MenuNewGame_->SetIsSClick(true);
		MenuLoad_->SetIsSClick(false);
		MenuExit_->SetIsSClick(false);
		break;

	case KEYBOARD::MenuLoad :
		MenuNewGame_->SetIsSClick(false);
		MenuLoad_->SetIsSClick(true);
		MenuExit_->SetIsSClick(false);
		break;

	case KEYBOARD::MenuExit :
		MenuNewGame_->SetIsSClick(false);
		MenuLoad_->SetIsSClick(false);
		MenuExit_->SetIsSClick(true);
		break;


	default:
		break;
	}


}