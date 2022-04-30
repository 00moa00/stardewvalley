#pragma once
#include "Items.h"

// Ό³Έν :
class Salad : public Items
{
public:
	static Salad* MainSalad;
	static Font* Font_;
	// constrcuter destructer
	Salad();
	~Salad();

	// delete Function
	Salad(const Salad& _Other) = delete;
	Salad(Salad&& _Other) noexcept = delete;
	Salad& operator=(const Salad& _Other) = delete;
	Salad& operator=(Salad&& _Other) noexcept = delete;

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

