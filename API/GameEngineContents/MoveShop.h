#pragma once
#include "Items.h"

// Ό³Έν :
class MoveShop : public Items
{
public:
	static MoveShop* MainMoveShop;

	// constrcuter destructer
	MoveShop();
	~MoveShop();

	// delete Function
	MoveShop(const MoveShop& _Other) = delete;
	MoveShop(MoveShop&& _Other) noexcept = delete;
	MoveShop& operator=(const MoveShop& _Other) = delete;
	MoveShop& operator=(MoveShop&& _Other) noexcept = delete;

private:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

};

