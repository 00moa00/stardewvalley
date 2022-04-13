#pragma once
#include "Items.h"
// Ό³Έν :
class MoveHouse : public Items
{
public:
	// constrcuter destructer
	MoveHouse();
	~MoveHouse();

	// delete Function
	MoveHouse(const MoveHouse& _Other) = delete;
	MoveHouse(MoveHouse&& _Other) noexcept = delete;
	MoveHouse& operator=(const MoveHouse& _Other) = delete;
	MoveHouse& operator=(MoveHouse&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

