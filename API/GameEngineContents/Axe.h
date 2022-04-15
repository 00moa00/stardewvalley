#pragma once
#include "Items.h"

// Ό³Έν :
class Axe : public Items
{
public:
	// constrcuter destructer
	Axe();
	~Axe();

	// delete Function
	Axe(const Axe& _Other) = delete;
	Axe(Axe&& _Other) noexcept = delete;
	Axe& operator=(const Axe& _Other) = delete;
	Axe& operator=(Axe&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

