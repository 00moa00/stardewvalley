#pragma once
#include "ShopItem.h"

// Ό³Έν :
class Parsnip_Shop : public ShopItem
{
public:
	// constrcuter destructer
	Parsnip_Shop();
	~Parsnip_Shop();

	// delete Function
	Parsnip_Shop(const Parsnip_Shop& _Other) = delete;
	Parsnip_Shop(Parsnip_Shop&& _Other) noexcept = delete;
	Parsnip_Shop& operator=(const Parsnip_Shop& _Other) = delete;
	Parsnip_Shop& operator=(Parsnip_Shop&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;

public:

	void InventoryNewItem() override;

protected:

private:

};

