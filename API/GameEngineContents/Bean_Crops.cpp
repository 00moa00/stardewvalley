#include "Bean_Crops.h"
#include "Items.h"
#include "Bean.h"

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
	GrowingCropsTime();

	//바뀐 순간에만 인덱스를 교체 
	if (GetGrowingDay() >= 1 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::BEAN_GROW1));
	}

	if (GetGrowingDay() >= 2 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::BEAN_GROW2));

	}

	if (GetGrowingDay() >= 3 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::BEAN_GROW3));

	}

	if (GetGrowingDay() >= 4 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::BEAN_GROW4));

	}

	if (GetGrowingDay() >= 7 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::BEAN_GROW5));
	}

	if (GetGrowingDay() >= 11 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::BEAN_GROW6));
		isHarvest_ = true;
	}

	if (GetGrowingDay() >= 12 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS && isHarvest_ == false)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::BEAN_GROW7));
	}
}

void Bean_Crops::DropCropsInMap()
{
	int Count = RandomItemCount.RandomInt(1, 3);
	Items* DropItem;

	for (int i = 0; i < Count; ++i)
	{
		DropItem = CreateDropItemActor<Bean>();
		DropItem->GetRenderer()->CameraEffectOn();
		float4 Pos;
		Pos.x = RandomItemPosX.RandomFloat(-60.f, 60.f);
		Pos.y = RamdomItemPosY.RandomFloat(-60.f, 60.f);

		DropItem->SetPosition({ this->GetPosition().x + Pos.x, this->GetPosition().y + Pos.y });
		DropItem->SetMoveFlag(true);
	}

	isHarvest_ = false;
	//this->Death();
}


