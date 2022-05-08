#pragma once
#include "Items.h"

// Ό³Έν :
class Coop : public Items
{
public:
	// constrcuter destructer
	Coop();
	~Coop();

	// delete Function
	Coop(const Coop& _Other) = delete;
	Coop(Coop&& _Other) noexcept = delete;
	Coop& operator=(const Coop& _Other) = delete;
	Coop& operator=(Coop&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

};

