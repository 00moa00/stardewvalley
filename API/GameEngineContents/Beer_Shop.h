#pragma once
#include "ShopItem.h"

// Ό³Έν :
class Beer_Shop : public ShopItem
{
public:
	// constrcuter destructer
	Beer_Shop();
	~Beer_Shop();

	// delete Function
	Beer_Shop(const Beer_Shop& _Other) = delete;
	Beer_Shop(Beer_Shop&& _Other) noexcept = delete;
	Beer_Shop& operator=(const Beer_Shop& _Other) = delete;
	Beer_Shop& operator=(Beer_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

public:
	void InventoryNewItem() override;
	bool MouseInItem() override;


};

