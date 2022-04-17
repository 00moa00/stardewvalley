#pragma once
#include "ShopItem.h"

// Ό³Έν :
class Daffodil_Shop : public ShopItem
{
public:
	// constrcuter destructer
	Daffodil_Shop();
	~Daffodil_Shop();

	// delete Function
	Daffodil_Shop(const Daffodil_Shop& _Other) = delete;
	Daffodil_Shop(Daffodil_Shop&& _Other) noexcept = delete;
	Daffodil_Shop& operator=(const Daffodil_Shop& _Other) = delete;
	Daffodil_Shop& operator=(Daffodil_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

protected:

private:

};

