#pragma once
#include "Items.h"
// Ό³Έν :
class MoveHouse : public Items
{
public:
	static MoveHouse* MainMoveHouse;
	// constrcuter destructer
	MoveHouse();
	~MoveHouse();

	// delete Function
	MoveHouse(const MoveHouse& _Other) = delete;
	MoveHouse(MoveHouse&& _Other) noexcept = delete;
	MoveHouse& operator=(const MoveHouse& _Other) = delete;
	MoveHouse& operator=(MoveHouse&& _Other) noexcept = delete;

private:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

};

