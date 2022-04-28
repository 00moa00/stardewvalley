#pragma once
#include "Effect.h"

// Ό³Έν :
class FlowerParticles : public Effect
{
public:
	// constrcuter destructer
	FlowerParticles();
	~FlowerParticles();

	// delete Function
	FlowerParticles(const FlowerParticles& _Other) = delete;
	FlowerParticles(FlowerParticles&& _Other) noexcept = delete;
	FlowerParticles& operator=(const FlowerParticles& _Other) = delete;
	FlowerParticles& operator=(FlowerParticles&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

public:
	GameEngineRandom RandomAnimation_;
	GameEngineRandom RandomSpeed_;

	float MaxY_;
	float Speed_;

public:
	void SetRandomAnimation(float _MaxY);

};

