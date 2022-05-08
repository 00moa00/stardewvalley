#pragma once
#include "Items.h"
class FarmTotem : public Items
{
public:
	static FarmTotem* MainFarmTotem;
	static Font* Font_;
	static ItemDataBox* MainItemDataBox;

	// constrcuter destructer
	FarmTotem();
	~FarmTotem();

	// delete Function
	FarmTotem(const FarmTotem& _Other) = delete;
	FarmTotem(FarmTotem&& _Other) noexcept = delete;
	FarmTotem& operator=(const FarmTotem& _Other) = delete;
	FarmTotem& operator=(FarmTotem&& _Other) noexcept = delete;

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

