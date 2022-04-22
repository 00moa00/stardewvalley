#include "Parsnip_Crops.h"
#include "MainUI.h"

Parsnip_Crops::Parsnip_Crops() 
{
}

Parsnip_Crops::~Parsnip_Crops() 
{
}

void Parsnip_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_SEED));
	CropRenderer_->CameraEffectOn();

}

void Parsnip_Crops::Update()
{

	switch (CropsUpdateState_)
	{
	case CROPS_UPDATE::INIT:

		if (MainUI::MainMainUI->isAddDay())
		{
			CropsUpdateState_ = CROPS_UPDATE::ADD_GROWING_DAY;
			break;
		}

		break;
	case CROPS_UPDATE::ADD_GROWING_DAY:

		StartDay_ = MainUI::MainMainUI->GetDay();
		GrowingDay_ = MainUI::MainMainUI->GetDay() - StartDay_;

		CropsUpdateState_ = CROPS_UPDATE::INIT;

		break;
	default:
		break;
	}



}

