#include "Inventory.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <sstream>


enum class UPDATE {
	POPUPINIT,
	POPUP,
	POPDOWN
};

Inventory::Inventory() 
	:
	BoxCollision_{nullptr},
	WildHorseradish_(nullptr),
	InventoryExit_(nullptr),
	Mouse_(nullptr),
	ItemCount_(0),
	UpdateState_(0),
	ItemStartIter(PlayerItemList_.begin()),
	ItemEndIter(PlayerItemList_.end()),

	MoveState_(ITEMMOVE::INIT)
{
}


Inventory::~Inventory() 
{
	Box_.clear();
	PlayerItemList_.clear();
}

void Inventory::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	Inventroy_ = CreateRenderer("inventory.bmp");
	Mouse_ = GetLevel()->CreateActor<Mouse>(static_cast<int>(PLAYLEVEL::MOUSE));
	InventoryExit_ = GetLevel()->CreateActor<InventoryExit>(static_cast<int>(PLAYLEVEL::ITEM));
	BoxInit();

	float4 Position;
	Position.x = this->GetPosition().x + (Inventroy_->GetScale().x / 2) + 25.f;
	Position.y = this->GetPosition().y + (Inventroy_->GetScale().y / 2) - 25.f;
	InventoryExit_->SetPosition({ Position.x ,Position.y });
	
	WildHorseradish2_ = NewItem<WildHorseradish>();

	WildHorseradish_ = NewItem<WildHorseradish>();
}


void Inventory::BoxInit()
{
	for (int i = 0; i < INVENTORY_MAX_COUNT; i++) {

		Box_.insert(std::make_pair(i,
			GetLevel()->CreateActor<InventroyBox>(static_cast<int>(PLAYLEVEL::INVENTROYBOX))));
	}

	//위치 초기화
	std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator EndIter = Box_.end();
	int count = 0;

	for (int y = 0; y < 3; ++y) {

		float BoxMargin = 0.f;

		if (y > 0) {
			BoxMargin = 10.f;
		}

		for (int x = 0; x < 12; ++x)
		{
			StartIter->second->SetPosition({ (GetPosition().x - 352.f) + (64.f * x), (GetPosition().y - 200.f) + (64.f * y + BoxMargin) });
			StartIter->second->CreateBoxCollision(count);
			count++;
			StartIter++;
		}

	}
}

void Inventory::AllUpdateOff()
{
	this->Off();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
		BoxStartIter->second->Off();
	}


	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {
		ItemStartIter->second->Off();
	}

	InventoryExit_->Off();

}


void Inventory::AllUpdateOn()
{
	this->On();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
		BoxStartIter->second->On();
	}

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {
		ItemStartIter->second->On();
	}

	InventoryExit_->On();

}


void Inventory::Update()
{

	//ItemStartIter = PlayerItemList_.begin();
	//ItemEndIter = PlayerItemList_.end();

	switch (MoveState_)
	{
	case ITEMMOVE::INIT:

		ItemStartIter = PlayerItemList_.begin();
		ItemEndIter = PlayerItemList_.end();

		MoveState_ = ITEMMOVE::NOTACT;

		break;

	case ITEMMOVE::NOTACT :

		if (ItemStartIter->second->MouseOver() && Mouse_->isMouseClick()) {

			ItemStartIter->second->SetInMouse(true);
			MoveState_ = ITEMMOVE::HOLD;
			break;
		}

		++ItemStartIter;

		if (ItemStartIter == ItemEndIter) {
			ItemStartIter = PlayerItemList_.begin();
		}

		break;

	case ITEMMOVE::HOLD:

		if (ItemStartIter->second->GetInMouse()) {

			ItemStartIter->second->SetPosition(Mouse_->GetPosition());
		}

		break;

	default:

		break;
	}



}

void Inventory::Render()
{
}

