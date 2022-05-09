#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

#include "MenuExit.h"
#include "InventroyBox.h"
#include "WildHorseradish.h"
#include "RendererData.h"
#include "InventoryCurrentFrame.h"
#include "Mouse.h"
#include "Player.h"
#include "ExitBotton.h"
#include "Items.h"
#include "PlayerPreview.h"
#include "PlayerCustomClothes.h"


//기본 아이템
#include "Hoe.h"
#include "EmptyItem.h"
#include "Axe.h"
#include "Pickaxe.h"
#include "Watering_Can.h"
#include "Parsnip_Seeds.h"
#include "Swoard.h"

#include "FarmTotem.h"
#include "MineTotem.h"



#include  <vector>
#include <map>
#include <memory>

enum class ITEMMOVE 
{
	INIT,
	NOTACT,
	ADDITER,
	HOLD,
	FREE,
	MINE,
	SWAP,
	SHOPPING
};

enum class POPUPSTATE 
{
	INIT,
	MINI,
	MAIN,
	SHOP,
	OFF
};

enum class INVEN_UPDATE
{
	INIT,
	UPDATE,
};

//#pragma warning(disable : 4267)
#define INVENTORY_MAX_COUNT 36

// 설명 :
class Inventory : public GameEngineActor
{
public:

	static Inventory* MainInventory;
	static ExitBotton* MainExitBotton;

	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	//Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void Render() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


private:

	void ItemMove();
	void InvenPopUp();
	void BoxInit();
	void InventoryPosInit();
	void ItemPosFocusInvenBox();
	void CurrentItemFrameFocusBox();

public:

	std::map<int, Items*> PlayerItemList_;
	std::map<int, InventroyBox*> Box_;
	

private:

	Mouse* Mouse_;								//충돌용 마우스
	PlayerPreview* PlayerPreview_;				//현재 커스텀 상태
	PlayerCustomClothes* PlayerCustomClothes_;	//현재 커스텀 의상

	GameEngineRenderer* Inventory_;				//인벤토리 보드(메뉴 보드)

	InventoryCurrentFrame* CurrentItemFrame_;	//현재 아이템을 가리키는 프레임
	Items* CurrentItem_;						//현재 선택하고 있는 아이템



	Hoe* Hoe_;					//초기 현재 아이템 등록용
	EmptyItem* EmptyItem_;		//빈 아이템

	ITEMMOVE MoveState_;			//메인 상태에서 움직이는 
	POPUPSTATE PopUpState_;			//조작에 의해 팝업 상태
	POPUPSTATE CurrentInvenState_;	//현재 팝업 상태, 바깥 체크용. 위의 변수는 idle이기때문에 확인하기 어렵다.
	INVEN_UPDATE UpdateState_;		//메인 업데이트 상태

	std::map<int, Items*>::iterator PlayerItemListStartIter;
	std::map<int, Items*>::iterator PlayerItemListEndIter;

	std::map<int, Items*>::iterator FindCurrentItemIter;

	std::map<int, InventroyBox*>::iterator BoxStartIter;
	std::map<int, InventroyBox*>::iterator BoxEndIter;

private:

	void SetCurrentItemFrame(Items* item_, InventroyBox* box_);
	void SetCurrentItemFrame(Items* item_);
	void SetCurrentItemFrame(InventroyBox* box_);

public:

	void AllUpdateOff();
	void AllUpdateOn();


	//================================
	//     Getter
	//================================

	std::map<int, Items*>::iterator FindPlayerListByValue(std::string ItemName)
	{
		std::map<int, Items*>::iterator StartIter = PlayerItemList_.begin();
		std::map<int, Items*>::iterator EndIter = PlayerItemList_.end();
		
		for (; StartIter != EndIter; ++StartIter)
		{
			if (StartIter->second->GetItemNameConstRef() == ItemName)
			{
				return StartIter;
			}
		}

		if (StartIter == EndIter)
		{
			return EndIter;
		}
	}

	Items* GetCurrentItem()
	{
		if (CurrentItem_ != nullptr)
		{
			return CurrentItem_;
		}

		else
		{
			return nullptr;
		}
	}

	Mouse* GetMouse()
	{
		return Mouse_;
	}

	bool GetCurrentItemEmpty()
	{
		return CurrentItem_ == EmptyItem_ && CurrentItem_ != nullptr;
	}

	bool GetPopUpStateShop()
	{
		return CurrentInvenState_ == POPUPSTATE::SHOP;
	}


	bool GetPopUpStateMini()
	{
		return CurrentInvenState_ == POPUPSTATE::MINI;
	}

	bool GetPopUpStateMain()
	{
		return CurrentInvenState_ == POPUPSTATE::MAIN;
	}

	bool ExitBottonMouseClick()
	{
		return MainExitBotton->MouseClick();
	}

	//================================
	//    Setter
	//================================

	void SetCurrentItem(Items* _SetItem)
	{
		CurrentItem_ = _SetItem;
	}

	void SetCurrentItemEmpty()
	{
		CurrentItem_ = EmptyItem_;
	}


	void SetCurrentItemParsnipSeed()
	{
		std::map<int, Items*>::iterator StartIter;
		std::map<int, Items*>::iterator EndIter;

		for (; StartIter != EndIter; ++StartIter)
		{
			if (StartIter->second->GetItemNameConstRef() == "Parsnip_Seeds")
			{
				CurrentItem_ = StartIter->second;

			}
		}

	}

	void SetPopUpStateMini()
	{
		PopUpState_ = POPUPSTATE::MINI;
	}

	void SetInventoryMoveStateInit()
	{
		MoveState_ = ITEMMOVE::INIT;
	}


	void FindAndErasePlayerItemList(std::string ItemName)
	{
		SetInventoryMoveStateInit();

		std::map<int, Items*>::iterator StartIter = PlayerItemList_.begin();
		std::map<int, Items*>::iterator EndIter = PlayerItemList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (StartIter->second->GetItemNameConstRef() == ItemName)
			{
				PlayerItemList_.erase(StartIter->first);
				return;
			}
		}

		if (StartIter == EndIter)
		{
			return;
		}

		CurrentItem_ = EmptyItem_;

	}

	
	void SetMiniInven(POPUPSTATE b)
	{
		PopUpState_ = b;
	}


	template<typename Actor>
	Actor* NewItem(float4 _AddPos = { 0, 0 })
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));


		//가지고 있는 아이템이라면 카운팅한다.

		std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
		std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

		for (; ItemStartIter != ItemEndIter; ++ItemStartIter) 
		{
			if (ItemStartIter->second->GetItemNameConstRef() == Item->GetItemNameConstRef())
			{
				ItemStartIter->second->AddItemCount();
				Item->Death();

				return nullptr;
			}
		}

		//아이템 생성
		std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
		std::map<int, InventroyBox*>::iterator EndIter = Box_.end();


		//앞에서부터 탐색해서 박스에 아이템이 없으면 그 자리에 넣기
		int index_ = 0;

		for (int i = 0; StartIter != EndIter; ++i) {

			std::map<int, Items*>::iterator ItemFindIter = PlayerItemList_.find(i);

			if (ItemFindIter == PlayerItemList_.end())
			{
				index_ = StartIter->first;
				break;
			}
			else
			{
				++StartIter;
			}

		}

		//플레이어 아이템리스트에 추가
		PlayerItemList_.insert(std::make_pair(index_, Item));

		//박스의 위치를 찾아서 등록
		std::map<int, InventroyBox*>::iterator FindIter = Box_.find(static_cast<const int>(index_));
		float4 Pos = FindIter->second->GetPosition();

		Item->SetPosition({ Pos + _AddPos });
		Item->GetRenderer()->CameraEffectOff();

		//++ItemCount_;
		return Item;
	}


	template<typename Actor>
	Actor* NewItem(int _Count)
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));

		//가지고 있는 아이템이라면 카운팅한다.

		std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
		std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

		for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
		{
			if (ItemStartIter->second->GetItemNameConstRef() == Item->GetItemNameConstRef())
			{
				Item->SetItemCount(_Count);
				Item->Death();

				return nullptr;
			}
		}

		//아이템 생성
		std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
		std::map<int, InventroyBox*>::iterator EndIter = Box_.end();


		//앞에서부터 탐색해서 박스에 아이템이 없으면 그 자리에 넣기
		int index_ = 0;

		for (int i = 0; StartIter != EndIter; ++i) {

			std::map<int, Items*>::iterator ItemFindIter = PlayerItemList_.find(i);

			if (ItemFindIter == PlayerItemList_.end())
			{
				index_ = StartIter->first;
				break;
			}
			else
			{
				++StartIter;
			}

		}

		//플레이어 아이템리스트에 추가
		PlayerItemList_.insert(std::make_pair(index_, Item));

		//박스의 위치를 찾아서 등록
		std::map<int, InventroyBox*>::iterator FindIter = Box_.find(static_cast<const int>(index_));
		float4 Pos = FindIter->second->GetPosition();

		Item->SetPosition({ Pos});
		Item->GetRenderer()->CameraEffectOff();
		Item->SetItemCount(_Count);
		return Item;
	}
};

