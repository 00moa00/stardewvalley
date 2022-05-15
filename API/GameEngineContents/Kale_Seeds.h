#pragma once
#include "Items.h"

// Ό³Έν :
class Kale_Seeds : public Items
{
public:
	static Kale_Seeds* MainKaleSeeds;
	static Font* Font_;
	static ItemDataBox* MainItemDataBox;

	// constrcuter destructer
	Kale_Seeds();
	~Kale_Seeds();

	// delete Function
	Kale_Seeds(const Kale_Seeds& _Other) = delete;
	Kale_Seeds(Kale_Seeds&& _Other) noexcept = delete;
	Kale_Seeds& operator=(const Kale_Seeds& _Other) = delete;
	Kale_Seeds& operator=(Kale_Seeds&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

public:
	Crops* CreateCrops() override;
	void AddItemCount() override;
	void SubItemCount() override;
	void UpdateOff() override;
	void UpdateOn() override;

};

