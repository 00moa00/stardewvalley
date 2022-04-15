#include "Parsnip_Seeds.h"

Parsnip_Seeds::Parsnip_Seeds() 
{
}

Parsnip_Seeds::~Parsnip_Seeds() 
{
}

void Parsnip_Seeds::Start()
{
	Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	Font_->ChangeWhiteColor();

	Font_->ChangeNumItem(1);
	//Font_->SetPositionItem({ GetPosition() });

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::PARSNIP_SEEDS));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	ItemType_ = ITEMTYPE::ITEM;

	SetItemName("Parsnip_Seeds");
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

