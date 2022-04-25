#pragma once
#include "Items.h"
// Ό³Έν :
class MoveForest : public Items
{
public:
	static MoveForest* MainMoveForest;


	// constrcuter destructer
	MoveForest();
	~MoveForest();

	// delete Function
	MoveForest(const MoveForest& _Other) = delete;
	MoveForest(MoveForest&& _Other) noexcept = delete;
	MoveForest& operator=(const MoveForest& _Other) = delete;
	MoveForest& operator=(MoveForest&& _Other) noexcept = delete;


private:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

};

