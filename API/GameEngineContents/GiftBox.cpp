#include "GiftBox.h"
#include "Inventory.h"
#include "Parsnip_Seeds.h"

GiftBox* GiftBox::MainGiftBox = nullptr;

GiftBox::GiftBox() 
	:
	OpenUpdate_(OPEN_UPDATE::WAIT)
{
}

GiftBox::~GiftBox() 
{
}

void GiftBox::Start()
{
	ItemRenderer_ = CreateRenderer("Giftbox.bmp");
	ItemRenderer_->SetIndex(0);
	ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::BOT);

	ItemRenderer_->CreateAnimation("Giftbox.bmp", "OPEN", 0, 9 , 0.200f, false);
	ItemRenderer_->CreateAnimation("Giftbox.bmp", "INIT", 0, 0, 0.200f, false);
	ItemRenderer_->ChangeAnimation("INIT");


	ItemCollider_ = CreateCollision("MapObject", { 48, 48 });

	ItemName_ = "GiftBox";

	ItemType_ = ITEMTYPE::GETITEM;

}

void GiftBox::Update()
{
	switch (OpenUpdate_)
	{
	case OPEN_UPDATE::WAIT:
		break;
	case OPEN_UPDATE::OPEN:

		ItemRenderer_->ChangeAnimation("OPEN");
		OpenUpdate_ = OPEN_UPDATE::GET;
		break;

	case OPEN_UPDATE::GET:

		if (ItemRenderer_->IsEndAnimation())
		{
			Inventory::MainInventory->NewItem<Parsnip_Seeds>(15);

			this->Death();
		}

	default:
		break;
	}
}

void GiftBox::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainGiftBox = this;
}

void GiftBox::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void GiftBox::GetItemAndAddInventory()
{
	 OpenUpdate_ = OPEN_UPDATE::OPEN;


}
