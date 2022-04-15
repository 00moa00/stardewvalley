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
#include "InventoryExit.h"
#include "Items.h"


//기본 아이템
#include "Hoe.h"
#include "Axe.h"
#include "Pickaxe.h"
#include "Watering_Can.h"



#include  <vector>
#include <map>
#include <memory>

enum class ITEMMOVE {
	INIT,
	NOTACT,
	ADDITER,
	HOLD,
	FREE,
	MINE
};

enum class MINIPOPUP {
	INIT,
	MINI,
	MAIN
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

	//static Inventory* MainInventory;
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	//Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;
	void LevelChangeStart() override;

	void LevelChangeEnd() override;

private:

	void ItemMove();
	void InvenPopUp();
	void BoxInit();
	void InventoryPosInit();
	void ItemPosFocusInvenBox();
public:

	Inventory& operator= (const Inventory& other)
	{

		if (0 < other.PlayerItemList_.size())
		{
			PlayerItemList_.insert(other.PlayerItemList_.begin(), other.PlayerItemList_.end());
		}

		if (0 < other.Box_.size())
		{
			Box_.insert(other.Box_.begin(), other.Box_.end());
		}

		//CurrentItemFrame_ = other.CurrentItemFrame_;
		//CurrentItem_ = other.CurrentItem_;

		UpdateState_ = INVEN_UPDATE::INIT;
		MoveState_ = ITEMMOVE::INIT;
		MiniState_ = MINIPOPUP::MINI;
		CurrentInvenState_ = MINIPOPUP::INIT;


		return *this;
	}


	template<typename Actor>
	Actor* NewItem(float4 _AddPos = {0, 0})
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));

		std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
		std::map<int, InventroyBox*>::iterator EndIter = Box_.end();

		//앞에서부터 탐색해서 아이템이 없으면 그 자리에 넣기
		int index_ = 0;

		for (; StartIter != EndIter; ) {
			if (!StartIter->second->IteminBox()) {
				index_ = StartIter->first;
				StartIter = EndIter;
			}
			if (StartIter != EndIter) { ++StartIter; }
		}

		//플레이어 아이템리스트에 추가
		PlayerItemList_.insert(std::make_pair(index_, Item));

		//박스의 위치를 찾아서 등록
		std::map<int, InventroyBox*>::iterator FindIter = Box_.find(static_cast<const int>(index_));
		float4 Pos = FindIter->second->GetPosition();

		Item->SetPosition({ Pos + _AddPos });
		//++ItemCount_;
		return Item;
	}


	void AllUpdateOff();

	void AllUpdateOn();

	bool InventoryExitMouseClick() {
		return InventoryExit_->MouseClick();
	}



	void SetMiniInven(MINIPOPUP b) {
		MiniState_ = b;
	}


	void SetCurrentItemFrame(Items* item_, InventroyBox* box_);
	void SetCurrentItemFrame(Items* item_);

	void SetCurrentItemFrameChange(InventroyBox* box_);

	Items* CurrentItem() {
		return CurrentItem_;
	}
	//bool GetisMiniInven() {
	//	return isMiniInven_;
	//}


private:
	
	std::map<int, Items*> PlayerItemList_;
	std::map<int, InventroyBox*> Box_;



	std::map<int, Items*>::iterator PlayerItemListStartIter;
	std::map<int, Items*>::iterator PlayerItemListEndIter;

	std::map<int, InventroyBox*>::iterator BoxStartIter;
	std::map<int, InventroyBox*>::iterator BoxEndIter;


	InventoryCurrentFrame* CurrentItemFrame_;

	GameEngineRenderer* Inventory_;
	// GameEngineCollision* BoxCollision_[INVENTORY_MAX_COUNT];
	Items* CurrentItem_;

	//bool isMiniInven_;


	//int ItemCount_;
	Mouse* Mouse_;
	InventoryExit* InventoryExit_;

	Hoe* Hoe_;
	Watering_Can* Watering_Can_;
	Axe* Axe_;
	Pickaxe* Pickaxe_;

	WildHorseradish* WildHorseradish_;

	ITEMMOVE MoveState_;
	MINIPOPUP MiniState_;
	MINIPOPUP CurrentInvenState_;
	INVEN_UPDATE UpdateState_;
};

