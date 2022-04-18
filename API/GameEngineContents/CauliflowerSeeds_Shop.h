#pragma once
#include "ShopItem.h"

// Ό³Έν :
class CauliflowerSeeds_Shop : public ShopItem
{
public:
	// constrcuter destructer
	CauliflowerSeeds_Shop();
	~CauliflowerSeeds_Shop();

	// delete Function
	CauliflowerSeeds_Shop(const CauliflowerSeeds_Shop& _Other) = delete;
	CauliflowerSeeds_Shop(CauliflowerSeeds_Shop&& _Other) noexcept = delete;
	CauliflowerSeeds_Shop& operator=(const CauliflowerSeeds_Shop& _Other) = delete;
	CauliflowerSeeds_Shop& operator=(CauliflowerSeeds_Shop&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;

public:

	void InventoryNewItem() override;
	bool MouseInItem() override;

protected:

private:

};

