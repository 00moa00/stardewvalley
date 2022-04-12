#pragma once
#include "Items.h"
// Ό³Έν :
class Tv : public Items
{
public:
	// constrcuter destructer
	Tv();
	~Tv();

	// delete Function
	Tv(const Tv& _Other) = delete;
	Tv(Tv&& _Other) noexcept = delete;
	Tv& operator=(const Tv& _Other) = delete;
	Tv& operator=(Tv&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

