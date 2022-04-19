#include "Parsnip_Seeds.h"

Parsnip_Seeds::Parsnip_Seeds() 
{
}

Parsnip_Seeds::~Parsnip_Seeds() 
{
}

void Parsnip_Seeds::Start()
{
	isPossibleHand_ = true;

	Name_ = "Parsnip_Seeds";
	FileName_ = "springobjects.bmp";

	FileIndex_ = static_cast<size_t>(ITEM::PARSNIP_SEEDS);

	Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	Font_->ChangeWhiteColor();

	Font_->ChangeNumItem(1);
	//Font_->SetPositionItem({ GetPosition() });

	ItemRenderer_ = CreateRenderer(FileName_);
	ItemRenderer_->SetIndex(FileIndex_);
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	ItemType_ = ITEMTYPE::ITEM;

	SellPrice_ = 35;
}

void Parsnip_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	case ITEM_STATE::ADDITEM:
		//	++Count_;
		Font_->ChangeNumItem(Count_);
		//	Font_->SetPositionItem({ GetPosition() });

		ItemState_ = ITEM_STATE::INIT;
		break;
	}

}

