#pragma once
#include "ShopItem.h"

// Ό³Έν :
class BeanStarter_Shop : public ShopItem
{
public:
	// constrcuter destructer
	BeanStarter_Shop();
	~BeanStarter_Shop();

	// delete Function
	BeanStarter_Shop(const BeanStarter_Shop& _Other) = delete;
	BeanStarter_Shop(BeanStarter_Shop&& _Other) noexcept = delete;
	BeanStarter_Shop& operator=(const BeanStarter_Shop& _Other) = delete;
	BeanStarter_Shop& operator=(BeanStarter_Shop&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;

public:

	void InventoryNewItem() override;
	bool MouseInItem() override;

protected:

private:

};

