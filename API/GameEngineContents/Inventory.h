#pragma once

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

#include "MenuExit.h"
#include "InventroyBox.h"
#include "WildHorseradish.h"
#include "RendererEnum.h"

#include "Mouse.h"

#include "Items.h"
#include  <vector>
#include <map>
#include <memory>

//#pragma warning(disable : 4267)
#define INVENTORY_MAX_COUNT 36

// 설명 :
class Inventory : public GameEngineActor
{
public:

	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

	void BoxInit();

public:

	void AllUpdateOff();

private:
	
	std::map<int, Items*> PlayerItemList_;
	std::map<int, InventroyBox*> Box_;

	GameEngineRenderer* Inventroy_;
	GameEngineCollision* BoxCollision_[INVENTORY_MAX_COUNT];
	bool isItem[INVENTORY_MAX_COUNT];
	

	int ItemCount_;
	WildHorseradish* WildHorseradish_;

	template<typename Actor>
	Actor* NewItem()
	{
		Actor* Item = nullptr;
		Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));

		//플레이어 아이템리스트에 추가
		PlayerItemList_.insert(std::make_pair(ItemCount_, Item));
	
	
		//박스의 위치를 찾아서 등록
		std::map<int, InventroyBox*>::iterator FindIter = Box_.find(static_cast<const int>(ItemCount_));
		float4 Pos = FindIter->second->GetPosition();

		Item->SetPosition({ Pos.x, Pos.y });
		++ItemCount_;
		return Item;
	}

	//template<typename ActorMouse>
	//bool ActorMouse()
	//{
	//	return 	ActorMouse->MouseClick();

	//}

	//GameEngineActor* actors[2];

};

