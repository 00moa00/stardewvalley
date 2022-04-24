#pragma once
#include "Items.h"

// Ό³Έν :
class Potato : public Items
{
public:
	static Potato* MainPotato;
	static Font* Font_;

	// constrcuter destructer
	Potato();
	~Potato();

	// delete Function
	Potato(const Potato& _Other) = delete;
	Potato(Potato&& _Other) noexcept = delete;
	Potato& operator=(const Potato& _Other) = delete;
	Potato& operator=(Potato&& _Other) noexcept = delete;

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

