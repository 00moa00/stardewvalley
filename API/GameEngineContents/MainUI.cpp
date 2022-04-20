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
	MinuteTime_(1),
	HourTime_(6),
	Day_(1),
	WeekIndex_(0),
	SecondTime_(21600),

	AmPm_(AM_PM::AM),
	MainUIRenderer_(nullptr),
	WeekRenderer_(nullptr),
//	Day_(nullptr),
	AmPmRenderer_(nullptr)
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
	MoneyFont_->ChangeNumUI(1000);
	MoneyFont_->SetPositionUI({ 1085.f, 192.f });

	//1188 128
	AmPmRenderer_ = CreateRenderer("am.bmp");
	AmPmRenderer_->CameraEffectOff();
	AmPmRenderer_->SetPivot({ 60.f, 12.f });

	//1150 67
	WeekRenderer_ = CreateRenderer("Week_Sheet .bmp");
	WeekRenderer_->CameraEffectOff();
	WeekRenderer_->SetPivot({ 0.f, -60.f });
	WeekRenderer_->SetIndex(static_cast<int>(WEEK::MON));

	//1119 128
	HourFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	HourFont_->ChangeNumUI(6);
	HourFont_->SetPositionUI({ 1119.f, 138.f });

	//1145 128
	MinuteFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	MinuteFont_->ChangeNumStr("00");
	MinuteFont_->SetPositionUI({ 1145.f, 138.f });

	//1145 128
	DayFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	DayFont_->ChangeNumUI(1);
	DayFont_->SetPositionUI({ GetPosition().x + 35.f, GetPosition().y  - 55.f});

	LevelRegist("MainUI");

}

void MainUI::Update()
{
	SecondTime_ = static_cast<int>(GetAccTime());
	
	//600초마다 10분이 추가됨.

	if (SecondTime_ >= 600 && SecondTime_ % 600 == 0)
	{
		MinuteTime_ += 10;
	}

	//10분마다 폰트 업데이트

	if (MinuteTime_ % 10 == 0)
	{
		MinuteFont_->ChangeNumUI(MinuteTime_);
	}


	//1시간이 되면 분 리셋, 폰트 업데이트

	if (MinuteTime_ % 60 == 0)
	{
		MinuteTime_ = 1;
		MinuteFont_->ChangeNumStr("00");

		HourTime_ += 1;
		HourFont_->ChangeNumUI(HourTime_);
	}

	//12시가 되면 오후로 바뀌고 1시로 다시 카운팅

	if (HourTime_ == 12 && AmPm_ == AM_PM::AM)
	{
		HourTime_ = 1;
		SetPm();
		AmPm_ = AM_PM::PM;
	}

	//오후 12시가 지나면 하루가 바뀜
	if (HourTime_ == 12 && AmPm_ == AM_PM::PM)
	{
		HourTime_ = 1;
		SetAm();
		AmPm_ = AM_PM::PM;
		AddWeek();
		++Day_;

	}


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
}

void MainUI::SetMainUIMoney(int _Money)
{
	MoneyFont_->ChangeNumUI(_Money);
}
