#include "TitleLevel.h"

#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include <GameEngine/GameEngineImage.h>

#include "Player.h"


//Player* TitleLevel::Player_;


TitleLevel::TitleLevel() 
	:	

	Timer_(2.f),

	isPopup_(false),
	KeyFlag_(false),

	TitleLogo_(nullptr),
	Title_(nullptr),

	TitleBackGround_(nullptr),
	TitleBackMountGreen(nullptr),
	TitleBackMountBlue(nullptr),
	TitleLeftFrontMount(nullptr),
	TitleRightFrontMount(nullptr),
	Mouse_(nullptr),
	CustomBoard_(nullptr),

	Bird_(),
	TitleCloud_(),
	MenuButton_(),

	TitleState_(TITLE_STATE::START)

{
	SetName("TitleLevel");

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


	//뉴게임스타트
	MenuButton_[0] = CreateActor<MenuButton>(static_cast<int>(TITLELEVEL::TITLELOGO));
	MenuButton_[0]->SetPosition({ GameEngineWindow::GetScale().Half().x - 250.f,GameEngineWindow::GetScale().Half().y + 250.f });
	MenuButton_[0]->CreateButtonRenderer("TitleMenuButtons.bmp", 0);
	MenuButton_[0]->CreateButtonCollision("NewGameStart", {222, 174});
	MenuButton_[0]->Off();

	//로드
	MenuButton_[1] = CreateActor<MenuButton>(static_cast<int>(TITLELEVEL::TITLELOGO));
	MenuButton_[1]->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y + 250.f });
	MenuButton_[1]->CreateButtonRenderer("TitleMenuButtons.bmp", 1);
	MenuButton_[1]->CreateButtonCollision("LoadGame", { 222, 174 });
	MenuButton_[1]->Off();

	//나가기
	MenuButton_[2] = CreateActor<MenuButton>(static_cast<int>(TITLELEVEL::TITLELOGO));
	MenuButton_[2]->SetPosition({ GameEngineWindow::GetScale().Half().x + 250.f , GameEngineWindow::GetScale().Half().y + 250.f });
	MenuButton_[2]->CreateButtonRenderer("TitleMenuButtons.bmp", 3);
	MenuButton_[2]->CreateButtonCollision("GameExit", { 222, 174 });
	MenuButton_[2]->Off();

	CustomBoard_ = CreateActor<CustomBoard>(static_cast<int>(TITLELEVEL::TITLELOGO));
	CustomBoard_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x ,GameEngineWindow::GetInst().GetScale().Half().y });

	CustomBoard_->GetRenderer()->CameraEffectOff();
	CustomBoard_->CustomBoardOff();


}	




void TitleLevel::Update()
{
	switch (TitleState_)
	{
	case TITLE_STATE::START:

		MoveFrontMount();
		MoveBackMount();
		MoveTitleLogo();
		MoveBird();
		SkipTitle();

		//타이틀 로고가 특정 위치까지 내려오면 메뉴바 팝업
		if ((TitleLogo_->GetPosition().y >= GameEngineWindow::GetScale().Half().y - 100.f))
		{
			TitleState_ = TITLE_STATE::POPUP;
		}

		break;
	case TITLE_STATE::POPUP:
		PopUpMenu();

		//마우스 클릭하면 전부 온
		if (Mouse_->isMouseClick())
		{
			MenuButton_[0]->On();
			MenuButton_[1]->On();
			MenuButton_[2]->On();
			TitleState_ = TITLE_STATE::WAIT;
		}

		break;
	case TITLE_STATE::WAIT:
		break;
	default:
		break;
	}

	MoveCloud();

	MenuButton_[0]->MouseOverChangeIndex();
	MenuButton_[1]->MouseOverChangeIndex();
	MenuButton_[2]->MouseOverChangeIndex();


	if (MenuButton_[0]->ButtonMouseOverAndLeftClick())
	{
		CustomBoard_->CustomBoardOn();
		TitleLogo_->Off();

		MenuButton_[0]->Off();
		MenuButton_[1]->Off();
		MenuButton_[2]->Off();

	}

	if (CustomBoard_->isClickBackButton() == true)
	{
		CustomBoard_->CustomBoardOff();
		TitleLogo_->On();

		MenuButton_[0]->On();
		MenuButton_[1]->On();
		MenuButton_[2]->On();

		CustomBoard_->SetClickBackButton(false);
	}



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

	Timer_ -= GameEngineTime::GetDeltaTime();

	if (Timer_ < 2.0f )
	{
		MenuButton_[0]->On();
	}

	if (Timer_ < 1.5f)
	{
		MenuButton_[1]->On();
	}


	if (Timer_ <1.0f)
	{
		MenuButton_[2]->On();

		TitleState_ = TITLE_STATE::WAIT;

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
		TitleState_ = TITLE_STATE::POPUP;
	}
}

