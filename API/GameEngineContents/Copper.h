#pragma once
#include "GameEngineContents/Items.h"

// Ό³Έν :
class Copper : public Items
{
public:
	static Font* Font_;
	static Copper* MainCopper;
	// constrcuter destructer
	Copper();
	~Copper();

	// delete Function
	Copper(const Copper& _Other) = delete;
	Copper(Copper&& _Other) noexcept = delete;
	Copper& operator=(const Copper& _Other) = delete;
	Copper& operator=(Copper&& _Other) noexcept = delete;

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

