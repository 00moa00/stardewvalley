#include "Parsnip_Crops.h"

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
	GrowingCropsTime();

	//바뀐 순간에만 인덱스를 교체 
	if ( GetGrowingDay() == 1 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW0));
	}
	
	if (GetGrowingDay() == 2 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW1));

	}

	if (GetGrowingDay() == 3 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW2));

	}

	if (GetGrowingDay() == 4 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW3));

	}

	if (GetGrowingDay() == 5 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW4));

	}
}

