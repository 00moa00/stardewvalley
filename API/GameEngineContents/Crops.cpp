#include "Crops.h"

Crops::Crops() 
	:
	MinuteTime_(0),
	HourTime_(6),
	Day_(1),
	SecondTime_(0),
	PrevSecondTime_(0),

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

void Crops::UpdateMinuteTime()
{
}

void Crops::UpdateHourTime()
{
}

void Crops::UpdateAddDay()
{
}

