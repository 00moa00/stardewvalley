#pragma once
#include "Items.h"

// Ό³Έν :
class Hitter : public Items
{
public:
	// constrcuter destructer
	Hitter();
	~Hitter();

	// delete Function
	Hitter(const Hitter& _Other) = delete;
	Hitter(Hitter&& _Other) noexcept = delete;
	Hitter& operator=(const Hitter& _Other) = delete;
	Hitter& operator=(Hitter&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

