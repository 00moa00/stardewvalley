#include "Cauliflower_Crops.h"

Cauliflower_Crops::Cauliflower_Crops() 
{
}

Cauliflower_Crops::~Cauliflower_Crops() 
{
}

void Cauliflower_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::CAULI_SEED));
	CropRenderer_->CameraEffectOn();
}

void Cauliflower_Crops::Update()
{
}

