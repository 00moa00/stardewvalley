#pragma once

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

#include "MenuExit.h"
#include "InventroyBox.h"
#include "WildHorseradish.h"
#include "RendererEnum.h"


#include "Items.h"
#include  <vector>
#include <map>
#include <memory>

//#pragma warning(disable : 4267)
#define INVENTORY_MAX_COUNT 36

// Ό³Έν :
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

	void BoxInit();


private:
	
	std::vector<Items*> PlayerItemList;
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

		PlayerItemList.push_back(Item);
		std::map<int, InventroyBox*>::iterator FindIter = Box_.find(static_cast<const int>(PlayerItemList.size() - 1));

		float4 Pos = FindIter->second->GetPosition();

		Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));
		Item->SetPosition({ Pos.x, Pos.y });

		return Item;
	}

	//template<typename ActorMouse>
	//bool ActorMouse()
	//{
	//	return 	ActorMouse->MouseClick();

	//}

	//GameEngineActor* actors[2];

};

