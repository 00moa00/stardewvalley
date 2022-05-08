#pragma once
#include "Items.h"
// Ό³Έν :
class Bean_Seeds : public Items
{
public:
	static Bean_Seeds* MainBeanSeeds;
	static Font* Font_;
	static ItemDataBox* MainItemDataBox;

	// constrcuter destructer
	Bean_Seeds();
	~Bean_Seeds();

	// delete Function
	Bean_Seeds(const Bean_Seeds& _Other) = delete;
	Bean_Seeds(Bean_Seeds&& _Other) noexcept = delete;
	Bean_Seeds& operator=(const Bean_Seeds& _Other) = delete;
	Bean_Seeds& operator=(Bean_Seeds&& _Other) noexcept = delete;

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

