#include "MainUI.h"
#include "RendererData.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"

#include <GameEngine/GameEngineLevel.h> 

MainUI* MainUI::MainMainUI = nullptr;

Font* MainUI::MoneyFont_ = nullptr;
Font* MainUI::MinuteFont_ = nullptr;
Font* MainUI::HourFont_ = nullptr;
Font* MainUI::DayFont_ = nullptr;


MainUI::MainUI() 
	:
	MinuteTime_(0),
	HourTime_(6),
	Day_(1),
	DayIndex_(0),
	SecondTime_(0),
	PrevSecondTime_(0),
	DayFadeAlpha_(0),
	AddTIme_(),
	ExtraHourTime_(0),
	SecondTimeInt_(0),


	isExtraDay_(false),

	AmPm_(AM_PM::AM),

	MinuteState_(MINUTE_STATE::COUNT),

	MainUIRenderer_(nullptr),
	DayRenderer_(nullptr),
	AmPmRenderer_(nullptr),
	DayFade_(nullptr),
	Font_(nullptr)
{
}

MainUI::~MainUI() 
{

}

void MainUI::Start()
{
	SetPosition({ GameEngineWindow::GetScale().x - (140.f / 1.5f) - 50.f,  (114.f / 1.5f) + 50.f });

	MainUIRenderer_ = CreateRenderer("UITop.bmp");
	MainUIRenderer_->CameraEffectOff();
	MainUIRenderer_->SetOrder((int)PLAYLEVEL::MAINUI);

	MoneyFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	MoneyFont_->ChangeNumMoneyLeftSort(1000, { 1230.f, 192.f });

	//1188 128
	AmPmRenderer_ = CreateRenderer("am.bmp");
	AmPmRenderer_->CameraEffectOff();
	AmPmRenderer_->SetPivot({ 60.f, 12.f });

	//1150 67
	DayRenderer_ = CreateRenderer("Week_Sheet.bmp");
	DayRenderer_->CameraEffectOff();
	DayRenderer_->SetPivot({ 20.f, -60.f });
	DayRenderer_->SetIndex(0);

	DayFade_ = CreateRenderer("DayFade.bmp");
	DayFade_->CameraEffectOff();
	DayFade_->SetOrder((int)PLAYLEVEL::FADE);
	DayFade_->SetAlpha(0);
	DayFade_->SetPivot({ -300 , 0 });

	//1119 128
	HourFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	HourFont_->ChangeNumLeftSort(6, { GetPosition().x - 3.f, GetPosition().y + 1.f});

	//1145 128
	MinuteFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	MinuteFont_->ChangeNumStr("00");
	MinuteFont_->ChangeNumLeftSort(10, { GetPosition().x + 32.f, GetPosition().y + 1.f });

	//1145 128
	DayFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	DayFont_->ChangeNumRightSort(1);
	DayFont_->SetPositionRightSort({ GetPosition().x + 55.f, GetPosition().y  - 55.f});

	LevelRegist("MainUI");


	//1145
}

void MainUI::Update()
{

	if (true == GameEngineInput::GetInst()->IsPress("TimeAdd"))
	{
		AddTIme_ = 10;
	}
	
	else
	{
		AddTIme_ = 0;
	}

	SecondTime_ = (GetAccTime());
	SecondTimeInt_ = static_cast<int>(SecondTime_) + 253;
	MinuteTime_ += AddTIme_;

	switch (MinuteState_)
	{
	case MINUTE_STATE::COUNT:

		if (SecondTimeInt_ % 7 == 0)
		{
			MinuteState_ = MINUTE_STATE::ADD;
			break;
		}

		break;

	case MINUTE_STATE::ADD:

		if (SecondTimeInt_ % 7 == 0)
		{
			MinuteTime_ += 10;
			PrevSecondTime_ = SecondTimeInt_;
			MinuteState_ = MINUTE_STATE::WAIT;

			break;
		}

		break;

	case MINUTE_STATE::WAIT:

		if (PrevSecondTime_ != SecondTimeInt_)
		{
			MinuteState_ = MINUTE_STATE::COUNT;
			break;
		}

		break;
	default:
		break;
	}

	UpdateMinuteFont();
	UpdateSetPm();
	UpdateSetAm();
	ExtraDayAndAddDay();
	UpdateHourTime();



	//if (HourTime_ > 18)
	//{
	//	DayFadeAlpha_ += (GameEngineTime::GetDeltaTime() + 20.f);
	//	DayFade_->SetAlpha(DayFadeAlpha_);

	//	if (DayFadeAlpha_ > 100)
	//	{
	//		DayFadeAlpha_ = 100;
	//		DayFade_->SetAlpha(DayFadeAlpha_);

	//	}

	//}


}

void MainUI::Render()
{

}

void MainUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMainUI = this;

	MoneyFont_ = MoneyFont_;
	MinuteFont_ = MinuteFont_;
	HourFont_ = HourFont_;
	DayFont_ = DayFont_;
}

void MainUI::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	MoneyFont_->NextLevelOn();
	MinuteFont_->NextLevelOn();
	HourFont_->NextLevelOn();
	DayFont_->NextLevelOn();
}


void MainUI::UpdateMinuteFont()
{
	//10분마다 폰트 업데이트
	if (MinuteTime_ > 0 && MinuteTime_ % 10 == 0)
	{
		MinuteFont_->ChangeNumLeftSort(MinuteTime_, { GetPosition().x + 32.f, GetPosition().y + 1.f });
		return;
	}
}

void MainUI::UpdateHourTime()
{
	//1시간이 되면 분 리셋, 폰트 업데이트
	if (MinuteTime_ > 0 && MinuteTime_ % 60 == 0)
	{
		MinuteTime_ = 0;
		MinuteFont_->ChangeNumStr("00");

		HourTime_ += 1;

		if (isExtraDay_ == false && AmPm_ == AM_PM::AM)
		{
			HourFont_->ChangeNumLeftSort(HourTime_, { GetPosition().x - 3.f, GetPosition().y + 1.f });
			return;
		}

		if (AmPm_ == AM_PM::PM)
		{
			HourFont_->ChangeNumLeftSort(HourTime_ - 12, { GetPosition().x - 3.f, GetPosition().y + 1.f });
			return;
		}


		if (isExtraDay_ == true && AmPm_ == AM_PM::AM)
		{
			HourFont_->ChangeNumLeftSort(HourTime_ - 24, { GetPosition().x - 3.f, GetPosition().y + 1.f });
			return;
		}
	}
}

void MainUI::UpdateSetPm()
{
	if (HourTime_ == 12 && AmPm_ == AM_PM::AM)
	{
		SetPm();
		AmPm_ = AM_PM::PM;
	}
}

void MainUI::UpdateSetAm()
{
	if (HourTime_ == 24 && AmPm_ == AM_PM::PM)
	{
		SetAm();
		AmPm_ = AM_PM::AM;
		isExtraDay_ = true;
		//HourTime_ = 0;
	}
}

void MainUI::ExtraDayAndAddDay()
{
	if (isExtraDay_ == true && HourTime_ == 25 && MinuteTime_==50)
	{
		AddDay();
		++Day_;
		DayFont_->ChangeNumRightSort(Day_);
		HourTime_ = 5;
		MinuteTime_ = 50;


		isExtraDay_ = false;
		Player::MainPlayer->ClearWetDirtTile();
		Player::MainPlayer->SetPlayerFaint();
		
	}
}

void MainUI::SetMainUIMoney(int _Money)
{
	MoneyFont_->ChangeNumMoneyLeftSort(_Money, { 1230.f, 192.f });
}

void MainUI::SetDayFadeReset()
{
	DayFadeAlpha_ = 0;
	DayFade_->SetAlpha(0);
}
