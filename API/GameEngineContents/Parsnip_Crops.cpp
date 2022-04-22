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
	SecondTime_ = (GetAccTime());
	SecondTimeInt_ = static_cast<int>(SecondTime_);

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

		MinuteTime_ += 10;
		PrevSecondTime_ = SecondTimeInt_;

		MinuteState_ = MINUTE_STATE::WAIT;

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

}

