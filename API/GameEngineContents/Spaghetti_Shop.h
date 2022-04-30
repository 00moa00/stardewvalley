#pragma once
#include "ShopItem.h"

// Ό³Έν :
class Spaghetti_Shop : public ShopItem
{
public:
	// constrcuter destructer
	Spaghetti_Shop();
	~Spaghetti_Shop();

	// delete Function
	Spaghetti_Shop(const Spaghetti_Shop& _Other) = delete;
	Spaghetti_Shop(Spaghetti_Shop&& _Other) noexcept = delete;
	Spaghetti_Shop& operator=(const Spaghetti_Shop& _Other) = delete;
	Spaghetti_Shop& operator=(Spaghetti_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

public:
	void InventoryNewItem() override;
	bool MouseInItem() override;


};

