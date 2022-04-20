#pragma once
#include "ShopItem.h"

// Ό³Έν :
class Parsnip_Shop : public ShopItem
{
public:
	static Parsnip_Shop* MainParsnipShop;

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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

public:

	void InventoryNewItem() override;
	bool MouseInItem() override;

protected:

private:

};

