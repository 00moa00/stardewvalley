#include "Cauliflower_Crops.h"
#include "Items.h"
#include "Cauliflower.h"

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
	GrowingCropsTime();

	//바뀐 순간에만 인덱스를 교체 
	if (GetGrowingDay() >= 1 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::CAULI_GROW1));
	}

	if (GetGrowingDay() >= 2 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::CAULI_GROW2));

	}

	if (GetGrowingDay() >= 4 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::CAULI_GROW3));

	}

	if (GetGrowingDay() >= 8 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::CAULI_GROW4));

	}

	if (GetGrowingDay() >= 12 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::CAULI_GROW4));

	}

	if (GetGrowingDay() >= 13 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::CAULI_GROW4));
		isHarvest_ = true;
	}
}

void Cauliflower_Crops::DropCropsInMap()
{
	int Count = RandomItemCount.RandomInt(1, 3);
	Items* DropItem;

	for (int i = 0; i < Count; ++i)
	{
		DropItem = CreateDropItemActor<Cauliflower>();
		DropItem->GetRenderer()->CameraEffectOn();
		float4 Pos;
		Pos.x = RandomItemPosX.RandomFloat(-20.f, 20.f);
		Pos.y = RamdomItemPosY.RandomFloat(-20.f, 20.f);

		DropItem->SetPosition({ this->GetPosition().x + Pos.x, this->GetPosition().y + Pos.y });
		DropItem->SetMoveFlag(true);
	}

	this->Death();
}

