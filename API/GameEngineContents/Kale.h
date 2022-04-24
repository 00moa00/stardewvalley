#pragma once
#include "Items.h"
// Ό³Έν :
class Kale : public Items
{
public:
	static Kale* MainKale;
	static Font* Font_;

	// constrcuter destructer
	Kale();
	~Kale();

	// delete Function
	Kale(const Kale& _Other) = delete;
	Kale(Kale&& _Other) noexcept = delete;
	Kale& operator=(const Kale& _Other) = delete;
	Kale& operator=(Kale&& _Other) noexcept = delete;

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

