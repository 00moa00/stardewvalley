#include "Crops.h"
#include "MainUI.h"

Crops::Crops() 
	:
	StartDay_(0),
	GrowingDay_(0),
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
	case CROPS_UPDATE::INIT:

		if (MainUI::MainMainUI->DayOver())
		{
			CropsUpdateState_ = CROPS_UPDATE::ADD_GROWING_DAY;
		}

		break;
	case CROPS_UPDATE::ADD_GROWING_DAY:

		GrowingDay_ = (MainUI::MainMainUI->GetDay()) - StartDay_;
		CropsUpdateState_ = CROPS_UPDATE::INIT;

		break;

	case CROPS_UPDATE::ADD_GROWING_DAY_INIT:

		StartDay_ = MainUI::MainMainUI->GetDay();
		GrowingDay_ = MainUI::MainMainUI->GetDay() - StartDay_;

		CropsUpdateState_ = CROPS_UPDATE::INIT;
		break;

	default:
		break;
	}

}

