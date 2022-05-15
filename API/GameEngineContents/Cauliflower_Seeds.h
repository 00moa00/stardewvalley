#pragma once
#include "Items.h"
// Ό³Έν :
class Cauliflower_Seeds : public Items
{
public:
	static Cauliflower_Seeds* MainCauliflowerSeeds;
	static Font* Font_;
	static ItemDataBox* MainItemDataBox;

	// constrcuter destructer
	Cauliflower_Seeds();
	~Cauliflower_Seeds();

	// delete Function
	Cauliflower_Seeds(const Cauliflower_Seeds& _Other) = delete;
	Cauliflower_Seeds(Cauliflower_Seeds&& _Other) noexcept = delete;
	Cauliflower_Seeds& operator=(const Cauliflower_Seeds& _Other) = delete;
	Cauliflower_Seeds& operator=(Cauliflower_Seeds&& _Other) noexcept = delete;

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

