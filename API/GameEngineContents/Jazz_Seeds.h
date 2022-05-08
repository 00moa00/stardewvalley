#pragma once
#include "Items.h"

// Ό³Έν :
class Jazz_Seeds : public Items
{
public:
	static Jazz_Seeds* MainJazzSeeds;
	static Font* Font_;
	static ItemDataBox* MainItemDataBox;

	// constrcuter destructer
	Jazz_Seeds();
	~Jazz_Seeds();

	// delete Function
	Jazz_Seeds(const Jazz_Seeds& _Other) = delete;
	Jazz_Seeds(Jazz_Seeds&& _Other) noexcept = delete;
	Jazz_Seeds& operator=(const Jazz_Seeds& _Other) = delete;
	Jazz_Seeds& operator=(Jazz_Seeds&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	Crops* CreateCrops() override;
	void AddItemCount() override;
	void SubItemCount() override;
	void UpdateOff() override;
	void UpdateOn() override;

};

