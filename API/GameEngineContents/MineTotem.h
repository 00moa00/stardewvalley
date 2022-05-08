#pragma once
#include "Items.h"

class MineTotem : public Items
{
public:
	static MineTotem* MainMineTotem;
	static Font* Font_;
	static ItemDataBox* MainItemDataBox;

	// constrcuter destructer
	MineTotem();
	~MineTotem();

	// delete Function
	MineTotem(const MineTotem& _Other) = delete;
	MineTotem(MineTotem&& _Other) noexcept = delete;
	MineTotem& operator=(const MineTotem& _Other) = delete;
	MineTotem& operator=(MineTotem&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

public:
	void AddItemCount() override;
	void SubItemCount() override;
	void UpdateOff() override;
	void UpdateOn() override;
	void SetItemCount(int _Count)override;

};