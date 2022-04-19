#include "TitleLevel.h"

#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include <GameEngine/GameEngineImage.h>


//Player* TitleLevel::Player_;


TitleLevel::TitleLevel() 
	:	TitleLogo_(nullptr),
		MenuExit_(nullptr),
		MenuLoad_(nullptr),
		MenuNewGame_(nullptr),
 		/*Player_(nullptr),*/
		TitleBackGround_(nullptr),
		Mouse_(nullptr),
		isPopup_(false),
		Timer_(0),
		KeyFlag_(false),
		MoveMenu_(0),
		CurrentMenu_(KEYBOARD::MenuNewGame)
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading() 
{

	TitleLogo_ = CreateActor<TitleLogo>((int)TITLELEVEL::TITLELOGO);

	Mouse_= CreateActor<Mouse>((int)TITLELEVEL::MOUSE);

	TitleBackGround_ = CreateActor<BackGround>((int)TITLELEVEL::BACKGROUND);


	//TitleBackGround_->GetRenderer()->SetImage();
}

void TitleLevel::Update()
{
	//¸Å´º¹Ù ÆË¾÷

	if ((TitleLogo_->GetPosition().y > GameEngineWindow::GetScale().Half().y - 100.f)
		&& isPopup_ == false) {

		AddTimer(GameEngineTime::GetDeltaTime() + 1.f);

		if (getTimer() > 150 && MenuNewGame_ == nullptr)
		{
			MenuNewGame_ = CreateActor<MenuNewGame>(2);
		}

		if (getTimer() > 300 && MenuLoad_ == nullptr)
		{
			MenuLoad_ = CreateActor<MenuLoad>(3);
		}


		if (getTimer() > 450 && MenuExit_== nullptr)
		{
			MenuExit_ = CreateActor<MenuExit>(4);
			isPopup_ = true;
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveRight") && CurrentMenu_ < KEYBOARD::MAX) 
	{
		++MoveMenu_;
		KeyFlag_ = true;
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft") && CurrentMenu_ > KEYBOARD::MenuNewGame) {
		--MoveMenu_;
		KeyFlag_ = true;

	}

	CurrentMenu_ = static_cast<KEYBOARD>(MoveMenu_);

	//	if (GetAsyncKeyState(MK_LBUTTON))
	//{
	//	GameEngine::GetInst().ChangeLevel("Play");
	//}

	//switch (CurrentMenu_)
	//{

	//case KEYBOARD::MenuNewGame :

	//	if(KeyFlag_) {
	//		MenuNewGame_->SetIsClick(true);
	//		MenuLoad_->SetIsClick(false);
	//		MenuExit_->SetIsClick(false);
	//		KeyFlag_ = false;
	//	}

	//	if (true == GameEngineInput::GetInst()->IsDown("LeftClick") && isPopup_ == true)
	//	{
	//		GameEngine::GetInst().ChangeLevel("Play");
	//	}

	//	break;

	//case KEYBOARD::MenuLoad :
	//	if (KeyFlag_) {
	//		MenuNewGame_->SetIsClick(false);
	//		MenuLoad_->SetIsClick(true);
	//		MenuExit_->SetIsClick(false);
	//		KeyFlag_ = false;
	//	}
	//	break;

	//case KEYBOARD::MenuExit :
	//	if (KeyFlag_) {
	//		MenuNewGame_->SetIsClick(false);
	//		MenuLoad_->SetIsClick(false);
	//		MenuExit_->SetIsClick(true);
	//		KeyFlag_ = false;
	//	}
	//	break;


	//default:
	//	break;
	//}


}

void TitleLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	TitleBackGround_->GetRenderer()->SetImage("titleback.bmp");
	TitleBackGround_->SetPosition(GameEngineWindow::GetScale().Half());

}
