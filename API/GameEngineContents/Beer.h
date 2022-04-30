#pragma once
#include "Items.h"

// Ό³Έν :
class Beer : public Items
{
public:
	static Beer* MainBear;
	static Font* Font_;

	// constrcuter destructer
	Beer();
	~Beer();

	// delete Function
	Beer(const Beer& _Other) = delete;
	Beer(Beer&& _Other) noexcept = delete;
	Beer& operator=(const Beer& _Other) = delete;
	Beer& operator=(Beer&& _Other) noexcept = delete;

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

