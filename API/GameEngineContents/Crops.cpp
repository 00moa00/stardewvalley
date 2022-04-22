#include "Crops.h"

Crops::Crops() 
	:
	StartDay_(0),
	GrowingDay_(0),
	CropsUpdateState_(CROPS_UPDATE::ADD_GROWING_DAY),
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


void Crops::GrowingCrops()
{

}

