#pragma once
#include  <vector>
#include <map>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include "MenuExit.h"
#include "InventroyBox.h"

#include "WildHorseradish.h"

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

private:

	void Start() override;
	void Update() override;
	void Render() override;

	void NewItem(GameEngineActor* _Item);
	void BoxInit();
	GameEngineRenderer* Inventroy_;
	std::vector<GameEngineActor*> PlayerItemList;

	std::map<int, InventroyBox*> Box_;
	GameEngineCollision* BoxCollision_[INVENTORY_MAX_COUNT];
	bool isItem[INVENTORY_MAX_COUNT];
	

	int ItemCount_;
	WildHorseradish* WildHorseradish_;

	template<typename Actor>
	Actor* NewItem()
	{

		Actor* Item = new Actor();
		//카운팅, 탐색 용
		PlayerItemList.push_back(Item);
		std::map<int, InventroyBox*>::iterator FindIter = Box_.find(PlayerItemList.size() - 1);

		float4 Pos = FindIter->second->GetPosition();

		Item = GetLevel()->CreateActor<Actor>(11);
		Item->SetPosition({ Pos.x, Pos.y });

		return Item;

	}


//	InventroyBox* InventroyBox_[36];
};

