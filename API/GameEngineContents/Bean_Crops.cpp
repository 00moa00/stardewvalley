#include "Bean_Crops.h"

Bean_Crops::Bean_Crops() 
{
}

Bean_Crops::~Bean_Crops() 
{
}

void Bean_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::BEAN_SEED));
	CropRenderer_->CameraEffectOn();
}
void Bean_Crops::Update()
{
}


