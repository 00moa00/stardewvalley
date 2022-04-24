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
		KeyFlag_(false)
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
	Title_ = CreateActor<Title>(static_cast<int>(TITLELEVEL::TITLELOGO));
	Mouse_ = CreateActor<Mouse>((int)TITLELEVEL::MOUSE);

	TitleLogo_ = CreateActor<TitleLogo>(static_cast<int>(TITLELEVEL::TITLELOGO));
	TitleLogo_ ->SetPosition({ GameEngineWindow::GetScale().x / 2, 0 });

	TitleCloud_[0] = CreateActor<BackGround>(static_cast<int>(TITLELEVEL::CLOUD));
	TitleCloud_[0]->GetRenderer()->SetImage("Title_Cloud.bmp");
	TitleCloud_[0]->SetPosition({ GameEngineWindow::GetScale().x, 720.f / 2 });

	TitleCloud_[1] = CreateActor<BackGround>(static_cast<int>(TITLELEVEL::CLOUD));
	TitleCloud_[1]->GetRenderer()->SetImage("Title_Cloud.bmp");
	TitleCloud_[1]->SetPosition({ GameEngineWindow::GetScale().x + GameEngineWindow::GetScale().x,  720.f / 2 });

	TitleCloud_[2] = CreateActor<BackGround>(static_cast<int>(TITLELEVEL::CLOUD));
	TitleCloud_[2]->GetRenderer()->SetImage("Title_Cloud.bmp");
	TitleCloud_[2]->SetPosition({ GameEngineWindow::GetScale().Half().x,  720.f / 2});


	TitleBackGround_ = CreateActor<BackGround>(static_cast<int>(TITLELEVEL::BACKGROUND));
	TitleBackGround_->GetRenderer()->SetImage("Title_Back.bmp");
	TitleBackGround_->SetPosition({ GameEngineWindow::GetScale().Half().x, 1500.f / 2 });

	TitleRightFrontMount = CreateActor<BackGround>(static_cast<int>(TITLELEVEL::FRONTMOUNT));
	TitleRightFrontMount->GetRenderer()->SetImage("FrontMountRight.bmp");
	TitleRightFrontMount-> SetPosition({ (GameEngineWindow::GetScale().Half().x) + 200.f, 1500.f / 2 });


	TitleLeftFrontMount = CreateActor<BackGround>(static_cast<int>(TITLELEVEL::FRONTMOUNT));
	TitleLeftFrontMount->GetRenderer()->SetImage("FrontMountLeft.bmp");
	TitleLeftFrontMount->SetPosition({ (GameEngineWindow::GetScale().Half().x) - 200.f, 1500.f / 2 });

	TitleBackMountBlue = CreateActor<BackGround>(static_cast<int>(TITLELEVEL::BACKMOUNTBLUE));
	TitleBackMountBlue->GetRenderer()->SetImage("BackMountBlue.bmp");
	TitleBackMountBlue->SetPosition({ GameEngineWindow::GetScale().Half().x, (1500.f / 2) });

	TitleBackMountGreen = CreateActor<BackGround>(static_cast<int>(TITLELEVEL::BACKMOUNTGREEN));
	TitleBackMountGreen->GetRenderer()->SetImage("BackMountGreen.bmp");
	TitleBackMountGreen->SetPosition({ GameEngineWindow::GetScale().Half().x, (1500.f / 2) });


	Bird_[0] = CreateActor<Bird>(static_cast<int>(TITLELEVEL::BIRD));
	Bird_[0]->SetPosition({GameEngineWindow::GetScale().Half().x, (1500.f / 2) + 350.f});

	Bird_[1] = CreateActor<Bird>(static_cast<int>(TITLELEVEL::BIRD));
	Bird_[1]->SetPosition({ GameEngineWindow::GetScale().Half().x + 100.f, (1500.f / 2) + 300.f });
}	




void TitleLevel::Update()
{

	MoveCloud();
	MoveFrontMount();
	MoveBackMount();
	PopUpMenu();
	MoveTitleLogo();
	MoveBird();

	SkipTitle();



}

void TitleLevel::MoveCloud()
{
	
	float4 Move = float4::LEFT;

	TitleCloud_[0]->SetMove(Move * GameEngineTime::GetDeltaTime() * 30.f);
	TitleCloud_[1]->SetMove(Move * GameEngineTime::GetDeltaTime() * 30.f);
	TitleCloud_[2]->SetMove(Move * GameEngineTime::GetDeltaTime() * 30.f);

	if (TitleCloud_[0]->GetPosition().x < -1280.f / 2)
	{
		TitleCloud_[0]->SetPosition({ 1280.f + 1280.f / 2, 720.f / 2 });
	}

	if (TitleCloud_[1]->GetPosition().x < -1280.f / 2)
	{
		TitleCloud_[1]->SetPosition({ 1280.f + 1280.f / 2  ,  720.f / 2 });
	}	

	if (TitleCloud_[2]->GetPosition().x < -1280.f)
	{
		TitleCloud_[2]->Death();
	}



}
void TitleLevel::MoveFrontMount()
{
	{
		float4 Move = float4::LEFT;
		TitleRightFrontMount->SetMove(Move * GameEngineTime::GetDeltaTime() * 100.f);

		if (TitleRightFrontMount->GetPosition().x < (1280.f / 2))
		{
			TitleRightFrontMount->SetPosition({ (1280.f / 2), 1500.f / 2 });
		}
	}


	{
		float4 Move = float4::RIGHT;
		TitleLeftFrontMount->SetMove(Move * GameEngineTime::GetDeltaTime() * 100.f);


		if (TitleLeftFrontMount->GetPosition().x > (1280.f / 2))
		{
			TitleLeftFrontMount->SetPosition({ (1280.f / 2), 1500.f / 2 });
		}
	}

}
void TitleLevel::MoveBackMount()
{
	if (Title_->GetPosition().y < 1500.f - GameEngineWindow::GetScale().Half().y
		&& Title_->GetPosition().y > 1500.f / 2)
	{

		{
			float4 Move = float4::UP;
			TitleBackMountBlue->SetMove(Move * GameEngineTime::GetDeltaTime() * 35.f);
		}

		{
			float4 Move = float4::UP;
			TitleBackMountGreen->SetMove(Move * GameEngineTime::GetDeltaTime() * 65.f);
		}
	}

}

void TitleLevel::MoveTitleLogo()
{
	if (Title_->GetPosition().y < 1500.f / 2
		&& TitleLogo_->GetPosition().y < GameEngineWindow::GetScale().Half().y - 100.f)
	{
		float4 Move = float4::DOWN;
		TitleLogo_->SetMove(Move * GameEngineTime::GetDeltaTime() * 50.f);
	}
}

void TitleLevel::MoveLogo()
{
}

void TitleLevel::PopUpMenu()
{
	if ((TitleLogo_->GetPosition().y >= GameEngineWindow::GetScale().Half().y - 100.f))
	{


		AddTimer(GameEngineTime::GetDeltaTime() + 1.f);

		if (getTimer() > 150 && MenuNewGame_ == nullptr)
		{
			MenuNewGame_ = CreateActor<MenuNewGame>(static_cast<int>(TITLELEVEL::TITLELOGO));
		}

		if (getTimer() > 250 && MenuLoad_ == nullptr)
		{
			MenuLoad_ = CreateActor<MenuLoad>(static_cast<int>(TITLELEVEL::TITLELOGO));
		}


		if (getTimer() > 350 && MenuExit_ == nullptr)
		{
			MenuExit_ = CreateActor<MenuExit>(static_cast<int>(TITLELEVEL::TITLELOGO));
			
		}

		if (Mouse_->isMouseClick())
		{
			Timer_ = 350;
		}
	}

}

void TitleLevel::MoveBird()
{
	float4 Move = float4::LEFT;
	Bird_[0]->SetMove(Move * GameEngineTime::GetDeltaTime() * 50.f);
	Bird_[1]->SetMove(Move * GameEngineTime::GetDeltaTime() * 50.f);
}

void TitleLevel::SkipTitle()
{
	if (Mouse_->isMouseClick())
	{
		Title_->SetPosition({ 0,0 });
		TitleLogo_->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 100.f });
	}
}

