#include "Crops.h"
#include "MainUI.h"
#include "Player.h"

Crops::Crops() 
	:
	StartDay_(0),
	GrowingDay_(0),
	TileFindIndex_(0),
	DirtDay_(0),

	isHarvest_(false),

	CropRenderer_(nullptr),

	RandomItemCount(),
	RandomItemPosX(),
	RamdomItemPosY(),

	CropsUpdateState_(CROPS_UPDATE::ADD_GROWING_DAY_INIT),
	MinuteState_(MINUTE_STATE::COUNT)

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

		//만약 첫날에 물이 뿌려져있으면 성장
		if (GrowingDay_ == 0 && isWetDirt())
		{
			StartDay_ -= 1;
		}

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
		CropsUpdateState_ = CROPS_UPDATE::GROWING_CROPS;

		break;

	case CROPS_UPDATE::GROWING_CROPS:


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
	//젖은 땅이거나 수확이 가능한 상태면 작물을 죽이지 않는다.
	if (isWetDirt() || isHarvest_ == true)
	{
		DirtDay_ = 0;	
		return;
	}

	else
	{
		++DirtDay_;
	}

	if (DirtDay_ == 2)
	{
		CropsDeath();
	}

}

void Crops::CropsDeath()
{
	Player::MainPlayer->DeleteSeedList(TileFindIndex_);
	this->Death();
}

void Crops::DropCropsInMap()
{
}

bool Crops::isWetDirt()
{

	return  Player::MainPlayer->FindWetDirt(TileFindIndex_);

}

