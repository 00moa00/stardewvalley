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
	PlayerItemListStartIter(PlayerItemList_.begin()),
	PlayerItemListEndIter(PlayerItemList_.end()),
	BoxStartIter(Box_.begin()),
	BoxEndIter(Box_.end()),

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
	//TODO: 예상되는 문제점, 플레이 도중에 아이템을 얻었을때 리스트가 변경되면서 이터레이터도 바뀔까?

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

		//아이템이 마우스와 충돌했고 클릭했다면 홀드
		if (PlayerItemListStartIter->second->MouseOver() && Mouse_->isMouseClick()) {

			MoveState_ = ITEMMOVE::HOLD;
			break;
		}

		++PlayerItemListStartIter;

		if (PlayerItemListStartIter == PlayerItemListEndIter) {
			PlayerItemListStartIter = PlayerItemList_.begin();
		}

		break;

	case ITEMMOVE::HOLD:

		//아이템을 마우스의 위치에 고정
		PlayerItemListStartIter->second->SetPosition(Mouse_->GetPosition());
		
		//마우스를 다시 한번 클릭했고, 마우스가 인벤토리 박스 안에 있으면 놓아주기 시도
		//TODO: 박스 밖에서 놓아주려했을떄 원래 자리로 돌아가게 하기.


	// TODO : 놓는 자리에 아이템이 있다면 하지 않는다. if (마우스 vs 아이템 == true + 홀딩중이 아닐때. )
		// 홀딩중일때 아이템의 플러그를 설정헌다. (NOATC 에서 )

		if ((Mouse_->isMouseClick() && Mouse_->MouseInBox()))
		{
			MoveState_ = ITEMMOVE::FREE;
		}

		break;


	case ITEMMOVE::FREE:


		for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
		{
			//if(BoxStartIter->second->GetInItem()) MoveState_ = ITEMMOVE::HOLD;

			//마우스와 충돌한 인벤토리 박스를 찾아서 그 박스의 위치에 아이템을 넣는다.
			if (BoxStartIter->second->MouseOver()) {

				//if(BoxStartIter->second->)

				//툴의 경우 사이즈가 다르다.
				if (PlayerItemListStartIter->second->GetItemType() == ITEMTYPE::TOOL) {

					float4 Pos = { BoxStartIter->second->GetPosition().x, BoxStartIter->second->GetPosition().y + 24.f };
					PlayerItemListStartIter->second->SetPosition(Pos);

				}

				else { 

					PlayerItemListStartIter->second->SetPosition(BoxStartIter->second->GetPosition());

				}
				MoveState_ = ITEMMOVE::INIT;
			}
		}
		break;


	default:

		break;
	}



}

void Inventory::Render()
{
}

