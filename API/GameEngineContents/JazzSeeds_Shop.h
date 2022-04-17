#pragma once
#include "ShopItem.h"

// Ό³Έν :
class JazzSeeds_Shop : public ShopItem
{
public:
	// constrcuter destructer
	JazzSeeds_Shop();
	~JazzSeeds_Shop();

	// delete Function
	JazzSeeds_Shop(const JazzSeeds_Shop& _Other) = delete;
	JazzSeeds_Shop(JazzSeeds_Shop&& _Other) noexcept = delete;
	JazzSeeds_Shop& operator=(const JazzSeeds_Shop& _Other) = delete;
	JazzSeeds_Shop& operator=(JazzSeeds_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

protected:

private:

};

