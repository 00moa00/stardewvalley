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


//기본 아이템
#include "Hoe.h"
#include "Axe.h"
#include "Pickaxe.h"
#include "Watering_Can.h"
#include "Parsnip_Seeds.h"


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
	SHOPPING
};

enum class POPUPSTATE 
{
	INIT,
	MINI,
	MAIN,
	SHOP
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

public:

	std::map<int, Items*> PlayerItemList_;
	std::map<int, InventroyBox*> Box_;
	

private:

	GameEngineRenderer* Inventory_;

	InventoryCurrentFrame* CurrentItemFrame_;
	Items* CurrentItem_;

	Mouse* Mouse_;
	ExitBotton* ExitBotton_;

	Hoe* Hoe_;

	ITEMMOVE MoveState_;
	POPUPSTATE PopUpState_;
	POPUPSTATE CurrentInvenState_;
	INVEN_UPDATE UpdateState_;

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


	bool ExitBottonMouseClick()
	{
		return ExitBotton_->MouseClick();
	}

	//================================
	//    Setter
	//================================


	void SetCurrentItemHoe()
	{
		CurrentItem_ = nullptr;
		//CurrentItem_ = Hoe_;
		//CurrentItemFrame_->SetPosition({ Hoe_->GetPosition().x,  Hoe_->GetPosition().y - 24.f });

	}

	void FindAndErasePlayerItemList(std::string ItemName)
	{

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
				ItemStartIter->second->SetItemStateAddItem();
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


};

