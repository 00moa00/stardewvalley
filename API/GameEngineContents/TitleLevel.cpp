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


}

void TitleLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	Title_ = CreateActor<Title>((int)TITLELEVEL::TITLELOGO);
	TitleLogo_ = CreateActor<TitleLogo>((int)TITLELEVEL::TITLELOGO);
	Mouse_ = CreateActor<Mouse>((int)TITLELEVEL::MOUSE);


	TitleCloud_[0] = CreateActor<BackGround>((int)TITLELEVEL::CLOUD);
	TitleCloud_[0]->GetRenderer()->SetImage("Title_Cloud.bmp");
	TitleCloud_[0]->SetPosition({ 1280.f, 720.f/2 });

	TitleCloud_[1] = CreateActor<BackGround>((int)TITLELEVEL::CLOUD);
	TitleCloud_[1]->GetRenderer()->SetImage("Title_Cloud.bmp");
	TitleCloud_[1]->SetPosition({ 1280.f + 1280.f,  720.f / 2 });


	TitleBackGround_ = CreateActor<BackGround>((int)TITLELEVEL::BACKGROUND);
	TitleBackGround_->GetRenderer()->SetImage("Title_Back.bmp");
	TitleBackGround_->SetPosition({ 1280.f / 2, 1500.f / 2 });

	TitleRightFrontMount = CreateActor<BackGround>((int)TITLELEVEL::FRONTMOUNT);
	TitleRightFrontMount->GetRenderer()->SetImage("FrontMountRight.bmp");
	TitleRightFrontMount-> SetPosition({ 1280.f / 2, 1500.f / 2 });


	TitleLeftFrontMout = CreateActor<BackGround>((int)TITLELEVEL::FRONTMOUNT);
	TitleLeftFrontMout->GetRenderer()->SetImage("FrontMountLeft.bmp");
	TitleLeftFrontMout->SetPosition({ 1280.f / 2, 1500.f / 2 });

	TitleBackMountBlue = CreateActor<BackGround>((int)TITLELEVEL::BACKMOUNTBLUE);
	TitleBackMountBlue->GetRenderer()->SetImage("BackMountBlue.bmp");
	TitleBackMountBlue->SetPosition({ 1280.f / 2, 1500.f / 2 });

	TitleBackMountGreen = CreateActor<BackGround>((int)TITLELEVEL::BACKMOUNTGREEN);
	TitleBackMountGreen->GetRenderer()->SetImage("BackMountGreen.bmp");
	TitleBackMountGreen->SetPosition({ 1280.f / 2, 1500.f / 2 });
}



void TitleLevel::Update()
{
	//¸Å´º¹Ù ÆË¾÷

	float4 Move = float4::LEFT;
	TitleCloud_[0]->SetMove(Move * GameEngineTime::GetDeltaTime() * 100.f);

	TitleCloud_[1]->SetMove(Move * GameEngineTime::GetDeltaTime() * 100.f);


	if (TitleCloud_[0]->GetPosition().x < -1280.f/2)
	{
		TitleCloud_[0]->SetPosition({ 1280.f + 1280.f/2, 720.f / 2 });
	}

	if (TitleCloud_[1]->GetPosition().x < -1280.f / 2)
	{
		TitleCloud_[1]->SetPosition({ 1280.f + 1280.f / 2  ,  720.f / 2 });
	}




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



}

