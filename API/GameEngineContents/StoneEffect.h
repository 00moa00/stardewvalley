#pragma once
#include "Effect.h"
#include "Particles.h"

// Ό³Έν :
class StoneEffect : public Effect
{
public:
	// constrcuter destructer
	StoneEffect();
	~StoneEffect();

	// delete Function
	StoneEffect(const StoneEffect& _Other) = delete;
	StoneEffect(StoneEffect&& _Other) noexcept = delete;
	StoneEffect& operator=(const StoneEffect& _Other) = delete;
	StoneEffect& operator=(StoneEffect&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

private:
	Particles* Particles_[8];

public:
	void SetParticlesPosition(float4 _Position) override;


};

