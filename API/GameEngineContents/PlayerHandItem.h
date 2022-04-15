#pragma once
#include "Items.h"

// Ό³Έν :
class PlayerHandItem : public Items
{
public:
	// constrcuter destructer
	PlayerHandItem();
	~PlayerHandItem();

	// delete Function
	PlayerHandItem(const PlayerHandItem& _Other) = delete;
	PlayerHandItem(PlayerHandItem&& _Other) noexcept = delete;
	PlayerHandItem& operator=(const PlayerHandItem& _Other) = delete;
	PlayerHandItem& operator=(PlayerHandItem&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

