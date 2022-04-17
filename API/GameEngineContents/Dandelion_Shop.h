#pragma once
#include "ShopItem.h"

// Ό³Έν :
class Dandelion_Shop : public ShopItem
{
public:
	// constrcuter destructer
	Dandelion_Shop();
	~Dandelion_Shop();

	// delete Function
	Dandelion_Shop(const Dandelion_Shop& _Other) = delete;
	Dandelion_Shop(Dandelion_Shop&& _Other) noexcept = delete;
	Dandelion_Shop& operator=(const Dandelion_Shop& _Other) = delete;
	Dandelion_Shop& operator=(Dandelion_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

protected:

private:

};

