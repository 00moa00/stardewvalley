#pragma once
#include "GameEngineContents//Items.h"

// Ό³Έν :
class DropWood : public Items
{
public:
	static Font* Font_;
	static DropWood* MainDropWood;
	// constrcuter destructer
	DropWood();
	~DropWood();

	// delete Function
	DropWood(const DropWood& _Other) = delete;
	DropWood(DropWood&& _Other) noexcept = delete;
	DropWood& operator=(const DropWood& _Other) = delete;
	DropWood& operator=(DropWood&& _Other) noexcept = delete;

private:

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void AddItemCount() override;
	void SubItemCount()override;
	void UpdateOff() override;
	void UpdateOn() override;

	//void MoveToPlayer();
};

