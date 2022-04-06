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
	isItem{false},
	WildHorseradish_(nullptr),
	Mouse_(nullptr),
	isPopUp_(true),
	ItemCount_(0),
	UpdateState_(0)
{
}

Inventory::~Inventory() 
{
	//PlayerItemList_.clear();
	//std::vector<Items*>().swap(PlayerItemList_);


	//for (std::map<int, InventroyBox*>::iterator it = Box_.begin(); it != Box_.end(); it++)
	//{
	//	delete it->second;
	//}

	Box_.clear();


}

void Inventory::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	Inventroy_ = CreateRenderer("inventory.bmp");
	BoxInit();
	

	WildHorseradish_ = NewItem<WildHorseradish>();
	//WildHorseradish_ = GetLevel()->CreateActor<WildHorseradish>(static_cast<int>(PlayLevel::ITEM));

}


void Inventory::BoxInit()
{

	for (int i = 0; i < INVENTORY_MAX_COUNT; i++) {

		Box_.insert(std::make_pair(i, GetLevel()->CreateActor<InventroyBox>(static_cast<int>(PLAYLEVEL::INVENTROYBOX))));

		//
		//std::stringstream CollisionBoxNum;
		//CollisionBoxNum << i;
		//BoxCollision_[i] = CreateCollision(CollisionBoxNum.str(), {148, 116});

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
	//this
	this->Off();

	//박스
	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();
	//int count = 0;

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
		BoxStartIter->second->Off();

	}

	//아이템 

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();
	//int count = 0;

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {
		ItemStartIter->second->Off();

	}

	
}

void Inventory::AllUpdateOn()
{

	//this
	this->On();

	//박스
	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();
	//int count = 0;

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
		BoxStartIter->second->On();

	}

	//아이템 

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();
	//int count = 0;

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {
		ItemStartIter->second->On();

	}


}



void Inventory::Update()
{
	//switch (static_cast<UPDATE>(UpdateState_))
	//{
	//	case UPDATE::POPUPINIT
	//}

}

void Inventory::Render()
{
}

