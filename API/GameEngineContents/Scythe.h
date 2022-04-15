#pragma once
#include "Items.h"

// Ό³Έν :
class Scythe : public Items
{
public:
	// constrcuter destructer
	Scythe();
	~Scythe();

	// delete Function
	Scythe(const Scythe& _Other) = delete;
	Scythe(Scythe&& _Other) noexcept = delete;
	Scythe& operator=(const Scythe& _Other) = delete;
	Scythe& operator=(Scythe&& _Other) noexcept = delete;

protected:

private:

};

