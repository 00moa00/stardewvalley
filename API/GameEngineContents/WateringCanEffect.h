#pragma once
#include "Effect.h"

// Ό³Έν :
class WateringCanEffect : public Effect
{
public:
	// constrcuter destructer
	WateringCanEffect();
	~WateringCanEffect();

	// delete Function
	WateringCanEffect(const WateringCanEffect& _Other) = delete;
	WateringCanEffect(WateringCanEffect&& _Other) noexcept = delete;
	WateringCanEffect& operator=(const WateringCanEffect& _Other) = delete;
	WateringCanEffect& operator=(WateringCanEffect&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

};

