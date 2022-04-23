#include "Tulip_Crops.h"
#include "Items.h"
#include "Tulip.h"


Tulip_Crops::Tulip_Crops() 
{
}

Tulip_Crops::~Tulip_Crops() 
{
}

void Tulip_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_-> SetIndex(static_cast<size_t>(CROPS::TULIP_SEED));
	CropRenderer_-> CameraEffectOn();
}

void Tulip_Crops::Update()
{
	GrowingCropsTime();

	//바뀐 순간에만 인덱스를 교체 
	if (GetGrowingDay() == 1 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::KALE_GROW1));
	}

	if (GetGrowingDay() == 2 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::KALE_GROW2));

	}

	if (GetGrowingDay() == 4 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::KALE_GROW3));

	}

	if (GetGrowingDay() == 6 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::KALE_GROW4));

	}


	if (GetGrowingDay() == 7 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::KALE_GROW4));
		isHarvest_ = true;
	}
}

void Tulip_Crops::DropCropsInMap()
{
	int Count = RandomItemCount.RandomInt(1, 3);
	Items* DropItem;

	for (int i = 0; i < Count; ++i)
	{
		DropItem = CreateDropItemActor<Tulip>();
		DropItem->GetRenderer()->CameraEffectOn();
		float4 Pos;
		Pos.x = RandomItemPosX.RandomFloat(-60.f, 60.f);
		Pos.y = RamdomItemPosY.RandomFloat(-60.f, 60.f);

		DropItem->SetPosition({ this->GetPosition().x + Pos.x, this->GetPosition().y + Pos.y });
		DropItem->SetMoveFlag(true);
	}

	this->Death();
}

