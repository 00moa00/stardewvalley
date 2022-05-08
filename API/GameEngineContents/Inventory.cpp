#include "Inventory.h"
#include "Player.h"
#include "Potato_Seeds.h"
#include "CoinAnimation.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <sstream>

//

Inventory* Inventory::MainInventory = nullptr;
ExitBotton* Inventory::MainExitBotton = nullptr;

enum class UPDATE {
	POPUPINIT,
	POPUP,
	POPDOWN
};

Inventory::Inventory()
	:
	
	Inventory_(nullptr),
	Mouse_(nullptr),
	CurrentItem_(nullptr),
	Hoe_(nullptr),
	CurrentItemFrame_(nullptr),
	PlayerPreview_(nullptr),
	PlayerCustomClothes_(nullptr),
	EmptyItem_(nullptr),

	CurrentInvenState_(POPUPSTATE::INIT),
	PopUpState_(POPUPSTATE::MINI),
	MoveState_(ITEMMOVE::INIT),
	UpdateState_(INVEN_UPDATE::INIT)

{

}


Inventory::~Inventory() 
{
	Box_.clear();
	PlayerItemList_.clear();
}

void Inventory::Start()
{
	//------< 액터 생성 >------------------------------------------------------------------
	
	CurrentItemFrame_ = GetLevel()->CreateActor<InventoryCurrentFrame>(static_cast<int>(PLAYLEVEL::CURRENTITEM));
	Mouse_ = GetLevel()->CreateActor<Mouse>(static_cast<int>(PLAYLEVEL::MOUSE));
	MainExitBotton = GetLevel()->CreateActor<ExitBotton>(static_cast<int>(PLAYLEVEL::ITEM));
	PlayerPreview_ = GetLevel()->CreateActor<PlayerPreview>(static_cast<int>(PLAYLEVEL::ITEM));
	PlayerCustomClothes_ = GetLevel()->CreateActor<PlayerCustomClothes>(static_cast<int>(PLAYLEVEL::ITEM));
	EmptyItem_ = GetLevel()->CreateActor<EmptyItem>(static_cast<int>(PLAYLEVEL::CURRENTITEM));


	//------< 초기화 >------------------------------------------------------------------

	SetPosition(GameEngineWindow::GetScale().Half());
	BoxInit();

	Inventory_ = CreateRenderer("inventory.bmp");
	Inventory_->CameraEffectOff();

	PlayerPreview_->SetPosition({this->GetPosition().x + 5.f, this->GetPosition().y + 150.f});
	PlayerCustomClothes_->SetPosition({ 0.f ,0.f });

	Hoe_ = NewItem<Hoe>();
	NewItem<Watering_Can>();
	NewItem<Axe>();
	NewItem<Pickaxe>();
	NewItem<WildHorseradish>();
	NewItem<Potato_Seeds>(3);
	NewItem<Swoard>();


	float4 Position;
	Position.x = Inventory_->GetScale().x  + 250.f;
	Position.y = Inventory_->GetScale().y  + 50.f;
	MainExitBotton->SetPosition({ Position.x ,Position.y - 100.f });
	
	LevelRegist("MainInventory");
}



void Inventory::Update()
{
	switch (UpdateState_)
	{
	case INVEN_UPDATE::INIT:

		PlayerPreview_->UpdateOff();
		PlayerCustomClothes_->UpdateOff();
		InventoryPosInit();
		ItemPosFocusInvenBox();

		CurrentItem_ = Hoe_;
		//CurrentItemFrame_->SetPosition(CurrentItem_->GetPosition());

		UpdateState_ = INVEN_UPDATE::UPDATE;
		break;

	case INVEN_UPDATE::UPDATE:
		//아이템은 박스의 위치를 무조건 따라감
		//ItemPosFocusInvenBox();
		InvenPopUp();
		ItemMove();
		CurrentItemFrameFocusBox();

		break;
	default:
		break;
	}



}

void Inventory::Render()
{

}

void Inventory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainInventory = this;
	MainExitBotton = MainExitBotton;
}

void Inventory::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
	{
		ItemStartIter->second->NextLevelOn();
	}

	std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator EndIter = Box_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter->second->NextLevelOn();
	}

	MainExitBotton->NextLevelOn();
	CurrentItemFrame_->NextLevelOn();
	Mouse_->NextLevelOn();
	PlayerPreview_->NextLevelOn();
	PlayerCustomClothes_->NextLevelOn();
	NextLevelOn();

}


void Inventory::BoxInit()
{
	for (int i = 0; i < INVENTORY_MAX_COUNT; i++) 
	{
		Box_.insert(std::make_pair(i, GetLevel()->CreateActor<InventroyBox>(static_cast<int>(PLAYLEVEL::INVENTROYBOX))));
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
	int BoxXMargin = 0;

	for (; StartIter != EndIter; ++StartIter)
	{
		if (StartIter->first == 12) 
		{
			BoxMargin = 10;
			BoxYMargin = 1;
			BoxXMargin = 0;
		}

		if (StartIter->first == 24) 
		{
			BoxYMargin = 2;
			BoxXMargin = 0;
		}

		StartIter->second->SetPosition({ (GetPosition().x - 352.f) + (64.f * BoxXMargin), (GetPosition().y - 200.f) + (64.f * BoxYMargin + BoxMargin) });
		++BoxXMargin;
	}
}

void Inventory::ItemPosFocusInvenBox()
{

	std::map<int, Items*>::iterator IterEndIter = PlayerItemList_.end();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) 
	{
		std::map<int, Items*>::iterator IterFindIter = PlayerItemList_.find(BoxStartIter->first);

		if (IterFindIter == IterEndIter) 
		{
			continue;
		}

		if (CurrentInvenState_ == POPUPSTATE::MINI)
		{
			//툴 아이템의 경우 피봇값이 달라서 프레임이 헛도는 일이 발생. 아래와 같이 해결
			if (IterFindIter->second->GetObjectType() == OBJECTTYPE::TOOL && IterFindIter->second->GetItemNameConstRef() != "Swoard")
			{
				IterFindIter->second->GetRenderer()->SetPivot({ 0, 0 });
				IterFindIter->second->SetPosition({ BoxStartIter->second->GetPosition().x, BoxStartIter->second->GetPosition().y + 24 });
			}
			else
			{
				IterFindIter->second->SetPosition(BoxStartIter->second->GetPosition());
			}
		}

		else if (CurrentInvenState_ == POPUPSTATE::MAIN)
		{
			if (IterFindIter->second->GetObjectType() == OBJECTTYPE::TOOL && IterFindIter->second->GetItemNameConstRef() != "Swoard")
			{
				IterFindIter->second->GetRenderer()->SetPivot({ 0, 24 });
				IterFindIter->second->SetPosition(BoxStartIter->second->GetPosition());

			}
			else
			{
				IterFindIter->second->SetPosition(BoxStartIter->second->GetPosition());
			}
		}
	}
}

void Inventory::CurrentItemFrameFocusBox()
{

	std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator EndIter = Box_.end();

	std::map<int, Items*>::iterator FindIter;
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (StartIter->second->MouseOverAndClick())
		{
			
			SetCurrentItemFrame(StartIter->second);
			FindIter = PlayerItemList_.find(StartIter->first);
			if (FindIter == ItemEndIter)
			{
				CurrentItem_ = EmptyItem_;
			}
		}

	}
}

void Inventory::AllUpdateOff()
{
	this->Off();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) 
	{
		BoxStartIter->second->Off();
	}


	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
	{
		ItemStartIter->second->UpdateOff();
	}

	MainExitBotton->Off();
	CurrentItemFrame_->Off();
	PlayerPreview_->UpdateOff();

}

void Inventory::AllUpdateOn()
{
	this->On();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
	{
		BoxStartIter->second->On();
	}

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter) 
	{
		ItemStartIter->second->UpdateOn();
	}

	MainExitBotton->On();
	CurrentItemFrame_->On();
	PlayerPreview_->UpdateOn();


}

void Inventory::SetCurrentItemFrame(Items* item_, InventroyBox* box_)
{
	if (item_->GetObjectType() == OBJECTTYPE::TOOL)
	{
		float4 Pos = { box_->GetPosition().x, box_->GetPosition().y  };
		CurrentItemFrame_->SetPosition(Pos);
	}

	else 
	{
		CurrentItemFrame_->SetPosition({ box_->GetPosition().x,  box_->GetPosition().y });
	}

}

void Inventory::SetCurrentItemFrame(Items* item_)
{

	if (item_->GetObjectType() == OBJECTTYPE::TOOL)
	{

		float4 Pos = { item_->GetPosition().x, item_->GetPosition().y - 24.f };
		CurrentItemFrame_->SetPosition(Pos);
	}

	else 
	{
		CurrentItemFrame_->SetPosition({ item_->GetPosition().x,  item_->GetPosition().y });
	
	}

}



void Inventory::SetCurrentItemFrame(InventroyBox* box_)
{

	float4 Pos = { box_->GetPosition().x, box_->GetPosition().y };
	CurrentItemFrame_->SetPosition(Pos);


}

void Inventory::ItemMove()
{
	//키값 변경용
	std::map<int, Items*>::iterator Finditer;
	std::map<int, InventroyBox*>::iterator FindBoxiter;


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

		ItemPosFocusInvenBox();


		for (; PlayerItemListStartIter != PlayerItemListEndIter; ++PlayerItemListStartIter)
		{

			if (PlayerItemListStartIter->second->MouseOver() && Mouse_->isMouseClick())
			{

				//상점일때 플레이어 툴은 팔지 않음.
				if (Player::MainPlayer->GetPlayerShoppingStateShopping())
				{
					if ((PlayerItemListStartIter->second->GetObjectType() == OBJECTTYPE::TOOL))
					{
						MoveState_ = ITEMMOVE::INIT;
						break;
					}

					MoveState_ = ITEMMOVE::SHOPPING;
					break;
				}

				//현재 아이템 프레임, 현재 아이템 저장
				SetCurrentItemFrame(  PlayerItemListStartIter->second);
				GameEngineSound::SoundPlayOneShot("pickUpItem.wav");

				CurrentItem_ = PlayerItemListStartIter->second;
				//FindCurrentItemIter

				//미니 상태에서 아이템은 이동할 수 없다.
				if ((CurrentInvenState_ == POPUPSTATE::MINI))
				{

					PlayerItemListStartIter->second->SetInBox(false);
					MoveState_ = ITEMMOVE::INIT;
					break;
				}

				PlayerItemListStartIter->second->SetInBox(false);
				PlayerItemListStartIter->second->SetInMouse(true);


				MoveState_ = ITEMMOVE::HOLD;
				break;
			}

		}

		if (PlayerItemListStartIter == PlayerItemListEndIter)
		{
			PlayerItemListStartIter = PlayerItemList_.begin();
		}


		break;

	case ITEMMOVE::HOLD:


		//아이템을 마우스의 위치에 고정
		PlayerItemListStartIter->second->SetPosition({Mouse_->GetPosition().x + 24.f, Mouse_->GetPosition().y + 30.f });

		//인벤토리 밖에서 클릭했다면
		//if (Mouse_->MouseClickInventoryOut())
		//{
		//	//해당 아이템이 음식이라면
		//	if (PlayerItemListStartIter->second->GetObjectType() == OBJECTTYPE::FOOD)
		//	{
		//		MainPlayer->
		//	}
		//}

		//인벤토리 밖에서 오른쪽 클릭 헸다면 
		if (Mouse_->MouseRightClickInventoryOut())
		{
			MoveState_ = ITEMMOVE::MINE;
		}

		//마우스를 다시 한번 클릭했고, 마우스가 인벤토리 박스 안에 있으면 놓아주기 시도
		if (Mouse_->MouseClickAndItemColl())
		{
			BoxStartIter = Box_.begin();
			BoxEndIter = Box_.end();

			for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
			{

				if (BoxStartIter->second->MouseOver())
				{
					Finditer = PlayerItemList_.find(BoxStartIter->first);

					//해당 위치에 아이템이 없다면 
					if (Finditer == PlayerItemListEndIter)
					{
						SetCurrentItemFrame(PlayerItemListStartIter->second, BoxStartIter->second);
						MoveState_ = ITEMMOVE::FREE;
						continue;
					}

					//놓으려는 자리에 아이템이 있다면
					if (Finditer->second->GetInBox() || Finditer->second->GetObjectType() == OBJECTTYPE::TOOL)
					{

						SetCurrentItemFrame(PlayerItemListStartIter->second, BoxStartIter->second);
						CurrentItem_ = Finditer->second;

						MoveState_ = ITEMMOVE::MINE;
						break;
					}

					//잡은 자리에 그대로 넣는다면
					if (Finditer->first == PlayerItemListStartIter->first)
					{
						SetCurrentItemFrame(PlayerItemListStartIter->second, BoxStartIter->second);
						MoveState_ = ITEMMOVE::MINE;
					}

				}
			}
		}

		break;

	case ITEMMOVE::SWAP:


		break;

	case ITEMMOVE::FREE:

		BoxStartIter = Box_.begin();
		BoxEndIter = Box_.end();

		for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
		{

			//마우스와 충돌한 인벤토리 박스를 찾아서 그 박스의 위치에 아이템을 넣는다.
			if (BoxStartIter->second->MouseOver())
			{
				GameEngineSound::SoundPlayOneShot("woodyStep.wav");

				PlayerItemListStartIter->second->SetInBox(true);
				PlayerItemListStartIter->second->SetInMouse(false);

				//키값 변경
				Finditer = PlayerItemListStartIter;
				std::swap(PlayerItemList_[BoxStartIter->first], Finditer->second);

				PlayerItemList_.erase(Finditer);

				MoveState_ = ITEMMOVE::INIT;
			}
		}
		break;

	case ITEMMOVE::MINE:

		FindBoxiter = Box_.find(PlayerItemListStartIter->first);
		PlayerItemListStartIter->second->SetPosition(FindBoxiter->second->GetPosition());

		GameEngineSound::SoundPlayOneShot("woodyStep.wav");
		PlayerItemListStartIter->second->SetInBox(true);
		PlayerItemListStartIter->second->SetInMouse(false);


		MoveState_ = ITEMMOVE::INIT;
		break;


	case ITEMMOVE::SHOPPING:

		if (Player::MainPlayer->GetMoneyAddMoneyCountWait())
		{
			Effect* Coin = GetLevel()->CreateActor<CoinAnimation>(static_cast<int>(PLAYLEVEL::SHOP_EFFECT));
			Coin->SetPosition({ PlayerItemListStartIter->second-> GetPosition().x + 96.f,  PlayerItemListStartIter->second->GetPosition().y });
			Coin->SetCount(PlayerItemListStartIter->second->GetSellPrice() / 5);

			Player::MainPlayer->AddMoney(PlayerItemListStartIter->second->GetSellPrice());
			PlayerItemListStartIter->second->SubItemCount();
		}

		MoveState_ = ITEMMOVE::INIT;

		break;

	default:

		break;
	}
}

void Inventory::InvenPopUp()
{

	if ((CurrentInvenState_ == POPUPSTATE::MINI)
		&& true == GameEngineInput::GetInst()->IsDown("OpenMenu"))
	{
		GameEngineSound::SoundPlayOneShot("bigDeSelect.wav");
		PopUpState_ = POPUPSTATE::MAIN;
	}

	if (((CurrentInvenState_ == POPUPSTATE::MAIN) 
		&& true == GameEngineInput::GetInst()->IsDown("OpenMenu")) || (MainExitBotton->MouseClick()))
	{
		GameEngineSound::SoundPlayOneShot("bigDeSelect.wav");
		PopUpState_ = POPUPSTATE::MINI;
	}

	//Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");

	if (Player::MainPlayer->GetisShopping())
	{
		PopUpState_ = POPUPSTATE::SHOP;
	}


	if (Player::MainPlayer->GetPlayerShoppingState() == PLAYER_SHOPPING::SHOP_OFF)
	{
		PopUpState_ = POPUPSTATE::MINI;
	}



	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();


	int BoxXMargin = 0;
	int BoxYMargin = 0;

	switch (PopUpState_)
	{
	case POPUPSTATE::INIT :

		break;

	case POPUPSTATE::MINI:

		CurrentInvenState_ = POPUPSTATE::MINI;

		PlayerPreview_->UpdateOff();
		PlayerCustomClothes_->UpdateOff();
		MainExitBotton->Off();

		CurrentItemFrame_->On();
		Inventory_->On();

		Inventory_->SetImage("MiniInven.bmp");
		SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y+300.f });
		
		for (; BoxStartIter != BoxEndIter; ++BoxStartIter) 
		{
			BoxStartIter->second->SetPosition({ (this->GetPosition().x - 352.f) + (64.f * BoxXMargin), (this->GetPosition().y) });
			if (BoxStartIter->first == 0) 
			{
				SetCurrentItemFrame(BoxStartIter->second);
			}
			
			++BoxXMargin;

			if (BoxStartIter->first > 11)
			{

				BoxStartIter->second->SetPosition({ 2000.f, (this->GetPosition().y) });

				//BoxStartIter->second->BoxCollision()->Off();
				BoxStartIter->second->Off();
			}
		}


		for (; ItemStartIter != ItemEndIter; ++ItemStartIter) 
		{
			if (ItemStartIter == ItemEndIter)
			{
				continue;
			}

			if (ItemStartIter->first > 11)
			{
				ItemStartIter->second->SetPosition({ 2000.f, (this->GetPosition().y) });

				ItemStartIter->second->UpdateOff();
			}
		}

	
		PopUpState_ = POPUPSTATE::INIT;

		break;

	case POPUPSTATE::MAIN:

		CurrentInvenState_ = POPUPSTATE::MAIN;

		CurrentItemFrame_->Off();

		MainExitBotton->On();
		PlayerPreview_->UpdateOn();
		PlayerCustomClothes_->UpdateOn();

		SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y});
		Inventory_->SetImage("inventory.bmp");


		for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
		{
			if (ItemStartIter == ItemEndIter)
			{
				continue;
			}

			ItemStartIter->second->UpdateOn();
		}

		for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
		{
			BoxStartIter->second->On();
		}


		InventoryPosInit();

		PopUpState_ = POPUPSTATE::INIT;
		break;

	case POPUPSTATE::SHOP:

		CurrentInvenState_ = POPUPSTATE::SHOP;

		MainExitBotton->Off();
		CurrentItemFrame_->Off();
		Inventory_->Off();
		PlayerPreview_->UpdateOff();
		PlayerCustomClothes_->UpdateOff();

		for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
		{
			if (ItemStartIter == ItemEndIter) 
			{
				continue;
			}

			ItemStartIter->second->UpdateOn();
		}

		BoxYMargin = 0;
		BoxXMargin = 0;

		BoxStartIter = Box_.begin();
		BoxEndIter = Box_.end();


		for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
		{
			BoxStartIter->second->On();
			//BoxStartIter->second->GetRenderer()->CameraEffectOff();

			if (BoxStartIter->first == 12)
			{
				BoxYMargin = 1;
				BoxXMargin = 0;
			}

			if (BoxStartIter->first == 24)
			{
				BoxYMargin = 2;
				BoxXMargin = 0;
			}

			BoxStartIter->second->SetPosition({ (362.f) + (64.f * BoxXMargin), (459.f) + (64.f * BoxYMargin ) });

			++BoxXMargin;
		}

		PopUpState_ = POPUPSTATE::INIT;
		break;

	case POPUPSTATE::OFF:

		CurrentInvenState_ = POPUPSTATE::OFF;

		MainExitBotton->Off();
		CurrentItemFrame_->Off();
		Inventory_->Off();
		PlayerPreview_->UpdateOff();


		for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
		{
			if (ItemStartIter == ItemEndIter)
			{
				continue;
			}

			ItemStartIter->second->UpdateOff();
		}

		for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
		{
			BoxStartIter->second->Off();

		}

		PopUpState_ = POPUPSTATE::INIT;
		break;
	}


}


