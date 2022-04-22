#pragma once

#include "Items.h"

// Ό³Έν :
class SmallWood1: public Items
{
public:
	// constrcuter destructer
	SmallWood1();
	~SmallWood1();

	// delete Function
	SmallWood1(const SmallWood1& _Other) = delete;
	SmallWood1(SmallWood1&& _Other) noexcept = delete;
	SmallWood1& operator=(const SmallWood1& _Other) = delete;
	SmallWood1& operator=(SmallWood1&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void DropItemInMap() override;
};

