#include "Jazz_Crops.h"
#include "Items.h"
#include "Jazz.h"

Jazz_Crops::Jazz_Crops() 
{
}

Jazz_Crops::~Jazz_Crops() 
{
}

void Jazz_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::JAZZ_SEED));
	CropRenderer_->CameraEffectOn();
}

void Jazz_Crops::Update()
{
	//�ٲ� �������� �ε����� ��ü 
	if (GetGrowingDay() == 1 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::JAZZ_GROW1));
	}

	if (GetGrowingDay() == 2 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::JAZZ_GROW2));

	}

	if (GetGrowingDay() == 4 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::JAZZ_GROW3));

	}

	if (GetGrowingDay() == 6 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::JAZZ_GROW4));

	}


	if (GetGrowingDay() == 8 && CropsUpdateState_ == CROPS_UPDATE::GROWING_CROPS)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::JAZZ_GROW4));
		isHarvest_ = true;
	}
}

void Jazz_Crops::DropCropsInMap()
{
	int Count = RandomItemCount.RandomInt(1, 3);
	Items* DropItem;

	for (int i = 0; i < Count; ++i)
	{
		DropItem = CreateDropItemActor<Jazz>();
		DropItem->GetRenderer()->CameraEffectOn();
		float4 Pos;
		Pos.x = RandomItemPosX.RandomFloat(-20.f, 20.f);
		Pos.y = RamdomItemPosY.RandomFloat(-20.f, 20.f);

		DropItem->SetPosition({ this->GetPosition().x + Pos.x, this->GetPosition().y + Pos.y });
		DropItem->SetMoveFlag(true);
	}

	this->Death();
}

bool Jazz_Crops::GetisDeath()
{
	return isDeath_;
}

