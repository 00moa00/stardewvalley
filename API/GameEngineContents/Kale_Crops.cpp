#include "Kale_Crops.h"
#include "Items.h"
#include "Kale.h"

Kale_Crops::Kale_Crops() 
{
}

Kale_Crops::~Kale_Crops() 
{
}

void Kale_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::KALE_SEED));
	CropRenderer_->CameraEffectOn();
}

void Kale_Crops::Update()
{
}

void Kale_Crops::DropCropsInMap()
{
	int Count = RandomItemCount.RandomInt(1, 3);
	Items* DropItem;

	for (int i = 0; i < Count; ++i)
	{
		DropItem = CreateDropItemActor<Kale>();
		DropItem->GetRenderer()->CameraEffectOn();
		float4 Pos;
		Pos.x = RandomItemPosX.RandomFloat(-60.f, 60.f);
		Pos.y = RamdomItemPosY.RandomFloat(-60.f, 60.f);

		DropItem->SetPosition({ this->GetPosition().x + Pos.x, this->GetPosition().y + Pos.y });
		DropItem->SetMoveFlag(true);
	}

	this->Death();
}
