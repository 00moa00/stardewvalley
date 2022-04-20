#pragma once
#include "ShopItem.h"

// Ό³Έν :
class ParsnipSeeds_Shop : public ShopItem
{
public:
	static ParsnipSeeds_Shop* MainParsnipSeedsShop;

	// constrcuter destructer
	ParsnipSeeds_Shop();
	~ParsnipSeeds_Shop();

	// delete Function
	ParsnipSeeds_Shop(const ParsnipSeeds_Shop& _Other) = delete;
	ParsnipSeeds_Shop(ParsnipSeeds_Shop&& _Other) noexcept = delete;
	ParsnipSeeds_Shop& operator=(const ParsnipSeeds_Shop& _Other) = delete;
	ParsnipSeeds_Shop& operator=(ParsnipSeeds_Shop&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

public:

	void InventoryNewItem() override;
	bool MouseInItem() override;

protected:

private:

};

