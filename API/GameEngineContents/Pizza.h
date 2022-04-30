#pragma once
#include "Items.h"

// Ό³Έν :
class Pizza : public Items
{
public:
	static Pizza* MainPizza;
	static Font* Font_;

	// constrcuter destructer
	Pizza();
	~Pizza();

	// delete Function
	Pizza(const Pizza& _Other) = delete;
	Pizza(Pizza&& _Other) noexcept = delete;
	Pizza& operator=(const Pizza& _Other) = delete;
	Pizza& operator=(Pizza&& _Other) noexcept = delete;

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

