#pragma once
#include "ShopItem.h"

// Ό³Έν :
class KaleSeeds_Shop : public ShopItem
{
public:
	// constrcuter destructer
	KaleSeeds_Shop();
	~KaleSeeds_Shop();

	// delete Function
	KaleSeeds_Shop(const KaleSeeds_Shop& _Other) = delete;
	KaleSeeds_Shop(KaleSeeds_Shop&& _Other) noexcept = delete;
	KaleSeeds_Shop& operator=(const KaleSeeds_Shop& _Other) = delete;
	KaleSeeds_Shop& operator=(KaleSeeds_Shop&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;

public:

	void InventoryNewItem() override;
	bool MouseInItem() override;

protected:

private:

};

