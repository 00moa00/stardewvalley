#pragma once
#include "Items.h"

// Ό³Έν :
class Watering_Can : public Items
{
public:
	static Watering_Can* MainWateringCan;

	// constrcuter destructer
	Watering_Can();
	~Watering_Can();

	// delete Function
	Watering_Can(const Watering_Can& _Other) = delete;
	Watering_Can(Watering_Can&& _Other) noexcept = delete;
	Watering_Can& operator=(const Watering_Can& _Other) = delete;
	Watering_Can& operator=(Watering_Can&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

};

