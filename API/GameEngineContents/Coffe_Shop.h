#pragma once
#include "ShopItem.h"

// Ό³Έν :
class Coffe_Shop : public ShopItem
{
public:
	// constrcuter destructer
	Coffe_Shop();
	~Coffe_Shop();

	// delete Function
	Coffe_Shop(const Coffe_Shop& _Other) = delete;
	Coffe_Shop(Coffe_Shop&& _Other) noexcept = delete;
	Coffe_Shop& operator=(const Coffe_Shop& _Other) = delete;
	Coffe_Shop& operator=(Coffe_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

public:
	void InventoryNewItem() override;
	bool MouseInItem() override;


};

