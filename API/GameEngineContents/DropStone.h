#pragma once
#include "GameEngineContents//Items.h"

// Ό³Έν :
class DropStone : public Items
{
public:
	static Font* Font_;
	static DropStone* MainDropStone;
	// constrcuter destructer
	DropStone();
	~DropStone();

	// delete Function
	DropStone(const DropStone& _Other) = delete;
	DropStone(DropStone&& _Other) noexcept = delete;
	DropStone& operator=(const DropStone& _Other) = delete;
	DropStone& operator=(DropStone&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void AddItemCount() override;
	void SubItemCount() override;
	void UpdateOff() override;
	void UpdateOn() override;

};

