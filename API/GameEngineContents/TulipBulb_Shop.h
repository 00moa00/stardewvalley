#pragma once
#include"ShopItem.h"

// Ό³Έν :
class TulipBulb_Shop : public ShopItem
{
public:
	// constrcuter destructer
	TulipBulb_Shop();
	~TulipBulb_Shop();

	// delete Function
	TulipBulb_Shop(const TulipBulb_Shop& _Other) = delete;
	TulipBulb_Shop(TulipBulb_Shop&& _Other) noexcept = delete;
	TulipBulb_Shop& operator=(const TulipBulb_Shop& _Other) = delete;
	TulipBulb_Shop& operator=(TulipBulb_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

protected:


};

