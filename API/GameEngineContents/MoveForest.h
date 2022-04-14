#pragma once
#include "Items.h"
// Ό³Έν :
class MoveForest : public Items
{
public:
	// constrcuter destructer
	MoveForest();
	~MoveForest();

	// delete Function
	MoveForest(const MoveForest& _Other) = delete;
	MoveForest(MoveForest&& _Other) noexcept = delete;
	MoveForest& operator=(const MoveForest& _Other) = delete;
	MoveForest& operator=(MoveForest&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

