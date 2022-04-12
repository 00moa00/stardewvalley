#include "Inventory.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <sstream>

//
//std::map<int, Items*> Inventory::PlayerItemList_;
////std::map<int, InventroyBox*> Inventory::Box_;


enum class UPDATE {
	POPUPINIT,
	POPUP,
	POPDOWN
};

Inventory::Inventory()
	:
	
	WildHorseradish_(nullptr),
	InventoryExit_(nullptr),
	Mouse_(nullptr),
	ItemCount_(0),
	UpdateState_(0),
	CurrentItem_(nullptr ),
	CurrentInvenState_(MINIPOPUP::INIT),
	MiniState_(MINIPOPUP::MINI),
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
//	SetPosition(GameEngineWindow::GetScale().Half());
	Inventroy_ = CreateRenderer("inventory.bmp");
	Inventroy_->CameraEffectOff();

	CurrentItemFrame_ = GetLevel()->CreateActor<InventoryCurrentFrame>(static_cast<int>(PLAYLEVEL::CURRENTITEM));

	Mouse_ = GetLevel()->CreateActor<Mouse>(static_cast<int>(PLAYLEVEL::MOUSE));
	InventoryExit_ = GetLevel()->CreateActor<InventoryExit>(static_cast<int>(PLAYLEVEL::ITEM));


	BoxInit();

	
	//게임 첫 시작은 숨기기
	CurrentItemFrame_->SetPosition({-50.f, -50.f});

	float4 Position;
	Position.x = Inventroy_->GetScale().x  + 250.f;
	Position.y = Inventroy_->GetScale().y  + 50.f;
	InventoryExit_->SetPosition({ Position.x ,Position.y });
	
	WildHorseradish2_ = NewItem<WildHorseradish>();

	WildHorseradish_ = NewItem<WildHorseradish>();
	//CurrentItem_ = WildHorseradish_;
	//CurrentItemFrame_->SetPosition(CurrentItem_->GetPosition());
}


void Inventory::BoxInit()
{
	for (int i = 0; i < INVENTORY_MAX_COUNT; i++) {

		Box_.insert(std::make_pair(i,
			GetLevel()->CreateActor<InventroyBox>(static_cast<int>(PLAYLEVEL::INVENTROYBOX))));
	}


	InventoryPosInit();

}

void Inventory::InventoryPosInit()
{

	//위치 초기화
	std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator EndIter = Box_.end();
	int count = 0;

	int BoxMargin = 0;
	int BoxYMargin = 0;
	float BoxXMargin = 0.f;

	for (; StartIter != EndIter; ++StartIter) {

		if (StartIter->first == 12) {
			BoxMargin = 10.f;
			BoxYMargin = 1;
			BoxXMargin = 0.f;
		}
		if (StartIter->first == 24) {
			//BoxYMargin = 20.f;
			BoxYMargin = 2;

			BoxXMargin = 0.f;
		}

		StartIter->second->SetPosition({ (GetPosition().x - 352.f) + (64.f * BoxXMargin), (GetPosition().y - 200.f) + (64.f * BoxYMargin + BoxMargin) });
		
		//박스 충돌체
		if (StartIter->second->BoxCollision() == nullptr) {
			StartIter->second->CreateBoxCollision(StartIter->first);
		}

		//현재 아이템 프레임 체인지
		if (StartIter->first == 0) SetCurrentItemFrameChange(StartIter->second);

		++BoxXMargin;
	}
}

void Inventory::ItemPosFocusInvenBox()
{

	std::map<int, Items*>::iterator IterEndIter = PlayerItemList_.end();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
		std::map<int, Items*>::iterator IterFindIter = PlayerItemList_.find(BoxStartIter->first);

		if (IterFindIter == IterEndIter) {
			continue;
		}

		//툴의 경우 사이즈가 다르다.
		if (IterFindIter->second->GetItemType() == ITEMTYPE::TOOL) {
		
	
			float4 Pos = { BoxStartIter->second->GetPosition().x, BoxStartIter->second->GetPosition().y + 24.f };
			IterFindIter->second->SetPosition(Pos);

		}

		else {

			IterFindIter->second->SetPosition(BoxStartIter->second->GetPosition());

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

void Inventory::SetCurrentItemFrame(Items* item_, InventroyBox* box_)
{
	if (item_->GetItemType() == ITEMTYPE::TOOL) {

		float4 Pos = { box_->GetPosition().x, box_->GetPosition().y  };
		CurrentItemFrame_->SetPosition(Pos);
	}

	else {
		CurrentItemFrame_->SetPosition({ box_->GetPosition().x,  box_->GetPosition().y });
	}

}

void Inventory::SetCurrentItemFrame(Items* item_)
{

	if (item_->GetItemType() == ITEMTYPE::TOOL) {

		float4 Pos = { item_->GetPosition().x, item_->GetPosition().y - 24.f };
		CurrentItemFrame_->SetPosition(Pos);
	}

	else {
		CurrentItemFrame_->SetPosition({ item_->GetPosition().x,  item_->GetPosition().y });
	
	}

}

void Inventory::SetCurrentItemFrameChange(InventroyBox* box_)
{

	if (CurrentItem_ != nullptr) {

		if (CurrentItem_->GetItemType() == ITEMTYPE::TOOL) {

			float4 Pos = { CurrentItemFrame_->GetPosition().x, box_->GetPosition().y};
			CurrentItemFrame_->SetPosition(Pos);
		}

		else {
			CurrentItemFrame_->SetPosition({ CurrentItemFrame_->GetPosition().x,  box_->GetPosition().y });

		}
	}

}

void Inventory::InvenPopUp()
{

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();


	int BoxXMargin = 0;

	switch (MiniState_)
	{
	case MINIPOPUP::INIT :

		break;

	case MINIPOPUP::MINI:

		CurrentInvenState_ = MINIPOPUP::MINI;

		InventoryExit_->Off();
		CurrentItemFrame_->On();


		Inventroy_->SetImage("MiniInven.bmp");
		SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y+300.f });
		
		for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {

			BoxStartIter->second->SetPosition({ (this->GetPosition().x - 352.f) + (64.f * BoxXMargin), (this->GetPosition().y) });
			if (BoxStartIter->first == 0) {
				SetCurrentItemFrameChange(BoxStartIter->second);

			}
			
			++BoxXMargin;

			if (BoxStartIter->first > 11){

				BoxStartIter->second->Off();
			}
		}


		for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {

			if (ItemStartIter == ItemEndIter) {
				continue;
			}

			if (ItemStartIter->first > 11)
				ItemStartIter->second->Off();
		}

	
		MiniState_ = MINIPOPUP::INIT;

		break;

	case MINIPOPUP::MAIN:

		CurrentInvenState_ = MINIPOPUP::MAIN;
		InventoryExit_->On();

		SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y});
		Inventroy_->SetImage("inventory.bmp");


		for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {

			if (ItemStartIter == ItemEndIter) {
				continue;
			}

			ItemStartIter->second->On();
		}

		for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
	
			BoxStartIter->second->On();
		}



		InventoryPosInit();

		MiniState_ = MINIPOPUP::INIT;

		break;

	}


}


void Inventory::Update()
{
	

	//키값 변경용
	std::map<int, Items*>::iterator Finditer;
	std::map<int, InventroyBox*>::iterator FindBoxiter;

	InvenPopUp();

	//TODO: 예상되는 문제점, 플레이 도중에 아이템을 얻었을때 리스트가 변경되면 INIT 해주기

	switch (MoveState_)
	{
	case ITEMMOVE::INIT:


		PlayerItemListStartIter = PlayerItemList_.begin();
		PlayerItemListEndIter = PlayerItemList_.end();

		BoxStartIter = Box_.begin();
		BoxEndIter = Box_.end();


		MoveState_ = ITEMMOVE::NOTACT;

		break;

	case ITEMMOVE::NOTACT:

		//아이템은 박스의 위치를 무조건 따라감
		ItemPosFocusInvenBox();

		for (; PlayerItemListStartIter != PlayerItemListEndIter; ++PlayerItemListStartIter) {


			if (PlayerItemListStartIter->second->MouseOver() && Mouse_->isMouseClick()) {
				
				//현재 아이템 프레임
				SetCurrentItemFrame(PlayerItemListStartIter->second);

				//현재 아이템 저장
				CurrentItem_ = PlayerItemListStartIter->second;


				//미니 상태에서 툴은 이동할 수 없다.
				if ((CurrentInvenState_ == MINIPOPUP::MINI) &&  (PlayerItemListStartIter->second->GetItemType() == ITEMTYPE::TOOL)) {
					PlayerItemListStartIter->second->SetInBox(false);
					MoveState_ = ITEMMOVE::INIT;
					break;
				}

				PlayerItemListStartIter->second->SetInBox(false);
				MoveState_ = ITEMMOVE::HOLD;
				break;
			}

			
			//break;
		}


		if (PlayerItemListStartIter == PlayerItemListEndIter) {
			PlayerItemListStartIter = PlayerItemList_.begin();
		}


		break;

	case ITEMMOVE::HOLD:

		//아이템을 마우스의 위치에 고정
		PlayerItemListStartIter->second->SetPosition(Mouse_->GetPosition());
		PlayerItemListStartIter->second->MouseHoldItem();


		//마우스를 다시 한번 클릭했고, 마우스가 인벤토리 박스 안에 있으면 놓아주기 시도
		//TODO : 박스 밖에서 놓아주려했을떄 원래 자리로 돌아가게 하기.
		//TODO : 아이템이 있는 위치에는 들고있는 아이템 변경하기

		if ((Mouse_->isMouseClick() && Mouse_->MouseInBox()))
		{

			BoxStartIter = Box_.begin();
			BoxEndIter = Box_.end();

			for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
			{

				if (BoxStartIter->second->MouseOver()) {

					//지정위치의 아이템이 해당 박스 안에 있다면 넘어가지 않는다.
					
					Finditer = PlayerItemList_.find(BoxStartIter->first);

					//해당 위치에 아이템이 없다면 
					if (Finditer == PlayerItemListEndIter) {
						SetCurrentItemFrame(PlayerItemListStartIter->second, BoxStartIter->second);
						MoveState_ = ITEMMOVE::FREE;
						continue;
					}

					 if (Finditer->second->GetInBox()) {

						MoveState_ = ITEMMOVE::HOLD;
					}


					 if (Finditer->first == PlayerItemListStartIter->first) {
						 SetCurrentItemFrame(PlayerItemListStartIter->second, BoxStartIter->second);
						 MoveState_ = ITEMMOVE::MINE;
					 }

				}
			}
		}

		break;


	case ITEMMOVE::FREE:

		BoxStartIter = Box_.begin();
		BoxEndIter = Box_.end();

		for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
		{

			//마우스와 충돌한 인벤토리 박스를 찾아서 그 박스의 위치에 아이템을 넣는다.
			if (BoxStartIter->second->MouseOver()) {

					PlayerItemListStartIter->second->SetInBox(true);

					//키값 변경
					Finditer = PlayerItemListStartIter;
					std::swap(PlayerItemList_[BoxStartIter->first], Finditer->second);

					PlayerItemList_.erase(Finditer);

					MoveState_ = ITEMMOVE::INIT;
			//	}
			}
		}
		break;

	case ITEMMOVE::MINE :
		
		FindBoxiter = Box_.find(PlayerItemListStartIter->first);

		PlayerItemListStartIter->second->SetPosition(FindBoxiter->second->GetPosition());
		MoveState_ = ITEMMOVE::INIT;

	default:

		break;
	}

}

void Inventory::Render()
{
}

