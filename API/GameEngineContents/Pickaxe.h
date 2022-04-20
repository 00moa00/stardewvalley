#pragma once
#include "Items.h"


// Ό³Έν :
class Pickaxe : public Items
{
public:
	static Pickaxe* MainPickaxe;

	// constrcuter destructer
	Pickaxe();
	~Pickaxe();

	// delete Function
	Pickaxe(const Pickaxe& _Other) = delete;
	Pickaxe(Pickaxe&& _Other) noexcept = delete;
	Pickaxe& operator=(const Pickaxe& _Other) = delete;
	Pickaxe& operator=(Pickaxe&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

