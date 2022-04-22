#include "Crops.h"
#include "MainUI.h"
#include "Player.h"

Crops::Crops() 
	:
	StartDay_(0),
	GrowingDay_(0),
	TileFindIndex_(0),
	DirtDay_(0),
	CropsUpdateState_(CROPS_UPDATE::ADD_GROWING_DAY_INIT),
	MinuteState_(MINUTE_STATE::COUNT),

	CropRenderer_(nullptr)
{
}

Crops::~Crops() 
{
}

void Crops::Start()
{
}

void Crops::Update()
{


}


void Crops::GrowingCropsTime()
{
	switch (CropsUpdateState_)
	{
	case CROPS_UPDATE::WAIT:


		if (MainUI::MainMainUI->DayEnd())
		{
			CropsUpdateState_ = CROPS_UPDATE::DAY_END_WETDIRT_CHECK;
			break;

		}

		break;

	case CROPS_UPDATE::DAY_END_WETDIRT_CHECK:

		DeathCropsCheck();
		CropsUpdateState_ = CROPS_UPDATE::DAY_OVER_WAIT;

		break;

	case CROPS_UPDATE::DAY_OVER_WAIT:


		if (MainUI::MainMainUI->DayOver())
		{
			CropsUpdateState_ = CROPS_UPDATE::ADD_GROWING_DAY;
			break;
		}

		break;

	case CROPS_UPDATE::ADD_GROWING_DAY:


		GrowingDay_ = (MainUI::MainMainUI->GetDay()) - StartDay_;
		CropsUpdateState_ = CROPS_UPDATE::WAIT;

		break;

	case CROPS_UPDATE::ADD_GROWING_DAY_INIT:

		StartDay_ = MainUI::MainMainUI->GetDay();
		GrowingDay_ = MainUI::MainMainUI->GetDay() - StartDay_;

		CropsUpdateState_ = CROPS_UPDATE::WAIT;
		
		break;

	default:
		break;
	}

}

void Crops::DeathCropsCheck()
{
	if (isWetDirt())
	{
		DirtDay_ = 0;	
	}

	else
	{
		++DirtDay_;
	}

	if (DirtDay_ == 2)
	{
		Player::MainPlayer->DeleteSeedList(TileFindIndex_);
		this->Death();
	}

}

bool Crops::isWetDirt()
{

	return  Player::MainPlayer->FindWetDirt(TileFindIndex_);

}

