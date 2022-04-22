#include "Patato_Crops.h"

Patato_Crops::Patato_Crops() 
{
}

Patato_Crops::~Patato_Crops() 
{
}

void Patato_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::POTATO_SEED));
	CropRenderer_->CameraEffectOn();
}

void Patato_Crops::Update()
{




}

