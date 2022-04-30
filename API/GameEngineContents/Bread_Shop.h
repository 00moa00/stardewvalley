#pragma once
#include "ShopItem.h"

// Ό³Έν :
class Bread_Shop : public ShopItem
{
public:
	// constrcuter destructer
	Bread_Shop();
	~Bread_Shop();

	// delete Function
	Bread_Shop(const Bread_Shop& _Other) = delete;
	Bread_Shop(Bread_Shop&& _Other) noexcept = delete;
	Bread_Shop& operator=(const Bread_Shop& _Other) = delete;
	Bread_Shop& operator=(Bread_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

public:
	void InventoryNewItem() override;
	bool MouseInItem() override;


};

