#pragma once
#include "Items.h"

// Ό³Έν :
class SmallStone : public Items
{
public:
	// constrcuter destructer
	
	SmallStone();
	~SmallStone();

	// delete Function
	SmallStone(const SmallStone& _Other) = delete;
	SmallStone(SmallStone&& _Other) noexcept = delete;
	SmallStone& operator=(const SmallStone& _Other) = delete;
	SmallStone& operator=(SmallStone&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void DropItemInMap() override;
};

