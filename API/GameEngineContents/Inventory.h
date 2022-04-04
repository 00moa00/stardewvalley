#pragma once
#include  <vector>
#include <map>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include "MenuExit.h"
#include "InventroyBox.h"

#include "Weeds.h"

#define INVENTORYCOUNT 36

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

	void NewItem(GameEngineActor* _Item);
	void BoxInit();
	GameEngineRenderer* Inventroy_;
	std::vector<GameEngineActor*> PlayerItemList;

	std::map<int, InventroyBox*> Box_;
	GameEngineCollision* BoxCollision_[INVENTORYCOUNT];
	bool isItem[INVENTORYCOUNT];
	

	int ItemCount_;
	Weeds* Weeds_;

//	InventroyBox* InventroyBox_[36];
};

