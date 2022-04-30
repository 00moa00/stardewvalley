#pragma once
#include "ShopItem.h"

// Ό³Έν :
class Salad_Shop : public ShopItem
{
public:
	// constrcuter destructer
	Salad_Shop();
	~Salad_Shop();

	// delete Function
	Salad_Shop(const Salad_Shop& _Other) = delete;
	Salad_Shop(Salad_Shop&& _Other) noexcept = delete;
	Salad_Shop& operator=(const Salad_Shop& _Other) = delete;
	Salad_Shop& operator=(Salad_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

public:
	void InventoryNewItem() override;
	bool MouseInItem() override;


};

