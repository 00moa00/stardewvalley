#pragma once
#include "Items.h"

// Ό³Έν :
class Kale_Seeds : public Items
{
public:
	static Kale_Seeds* MainKaleSeeds;
	static Font* Font_;

	// constrcuter destructer
	Kale_Seeds();
	~Kale_Seeds();

	// delete Function
	Kale_Seeds(const Kale_Seeds& _Other) = delete;
	Kale_Seeds(Kale_Seeds&& _Other) noexcept = delete;
	Kale_Seeds& operator=(const Kale_Seeds& _Other) = delete;
	Kale_Seeds& operator=(Kale_Seeds&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;

};

