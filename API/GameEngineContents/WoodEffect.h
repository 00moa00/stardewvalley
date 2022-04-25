#pragma once
#include "Effect.h"
#include "Particles.h"

// Ό³Έν :
class WoodEffect : public Effect
{
public:
	// constrcuter destructer
	WoodEffect();
	~WoodEffect();

	// delete Function
	WoodEffect(const WoodEffect& _Other) = delete;
	WoodEffect(WoodEffect&& _Other) noexcept = delete;
	WoodEffect& operator=(const WoodEffect& _Other) = delete;
	WoodEffect& operator=(WoodEffect&& _Other) noexcept = delete;
private:
	void Start() override;
	void Update() override;

	Particles* Particles_[8];

public:

	void SetParticlesPosition(float4 _Position) override;

};

