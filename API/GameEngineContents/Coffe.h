#pragma once
#include "Items.h"

// Ό³Έν :
class Coffe : public Items
{
public:
	static Coffe* MainCoffe;
	static Font* Font_;

	// constrcuter destructer
	Coffe();
	~Coffe();

	// delete Function
	Coffe(const Coffe& _Other) = delete;
	Coffe(Coffe&& _Other) noexcept = delete;
	Coffe& operator=(const Coffe& _Other) = delete;
	Coffe& operator=(Coffe&& _Other) noexcept = delete;

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

