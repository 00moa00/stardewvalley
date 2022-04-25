#pragma once
#include "Items.h"
// Ό³Έν :
class Parsnip_Seeds : public Items
{
public:

	static Parsnip_Seeds* MainParsnipSeeds;
	static Font* Font_;

	// constrcuter destructer
	Parsnip_Seeds();
	~Parsnip_Seeds();

	// delete Function
	Parsnip_Seeds(const Parsnip_Seeds& _Other) = delete;
	Parsnip_Seeds(Parsnip_Seeds&& _Other) noexcept = delete;
	Parsnip_Seeds& operator=(const Parsnip_Seeds& _Other) = delete;
	Parsnip_Seeds& operator=(Parsnip_Seeds&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

public:
	Crops* CreateCrops() override;

	void AddItemCount() override;
	void SubItemCount() override;
	void SetItemCount(int _Count)override;

	void UpdateOff() override;
	void UpdateOn() override;

};

