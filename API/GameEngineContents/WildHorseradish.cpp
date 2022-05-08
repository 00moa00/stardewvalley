#include "WildHorseradish.h"
#include "Inventory.h"

WildHorseradish* WildHorseradish::MainWildHorseradish = nullptr;

WildHorseradish::WildHorseradish(){

}

WildHorseradish::~WildHorseradish()
{
}

void WildHorseradish::Start()
{

	ItemRenderer_= CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WILD_HORSERADISH));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_= CreateCollision("Item", { 40, 40 });
	
	SetItemName("WildHorseradish");

	ItemType_ = ITEMTYPE::GATHERING;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::WILD_HORSERADISH);

	SellPrice_ = 35;

}

void WildHorseradish::Update()
{
}

void WildHorseradish::Render()
{
}

void WildHorseradish::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainWildHorseradish = this;
}

void WildHorseradish::AddItemCount()
{
	++ItemCount_;
}

void WildHorseradish::SubItemCount()
{
	if (ItemCount_ == 1)
	{
		ItemCount_ = 0;
		Player::MainPlayer->SetResetPlayerHandItem();
		Inventory::MainInventory->FindAndErasePlayerItemList(this->GetItemNameConstRef());
		this->Death();
	}
	else
	{
		--ItemCount_;
	}
}

void WildHorseradish::UpdateOff()
{
	this->Off();
}

void WildHorseradish::UpdateOn()
{
	this->On();

}
