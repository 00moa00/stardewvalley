#pragma once
#include "Items.h"

// Ό³Έν :
class Swoard : public Items
{
public:
	static Swoard* MainSwoard;

	// constrcuter destructer
	Swoard();
	~Swoard();

	// delete Function
	Swoard(const Swoard& _Other) = delete;
	Swoard(Swoard&& _Other) noexcept = delete;
	Swoard& operator=(const Swoard& _Other) = delete;
	Swoard& operator=(Swoard&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


};

