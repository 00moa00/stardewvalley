#pragma once
#include "Items.h"

// Ό³Έν :
class MiniWood : public Items
{
public:
	// constrcuter destructer
	MiniWood();
	~MiniWood();

	// delete Function
	MiniWood(const MiniWood& _Other) = delete;
	MiniWood(MiniWood&& _Other) noexcept = delete;
	MiniWood& operator=(const MiniWood& _Other) = delete;
	MiniWood& operator=(MiniWood&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	//void MoveToPlayer();
};

