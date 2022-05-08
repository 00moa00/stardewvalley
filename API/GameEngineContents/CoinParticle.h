#pragma once
#include "Effect.h"

// Ό³Έν :
class CoinParticle : public Effect
{
public:
	// constrcuter destructer
	CoinParticle();
	~CoinParticle();

	// delete Function
	CoinParticle(const CoinParticle& _Other) = delete;
	CoinParticle(CoinParticle&& _Other) noexcept = delete;
	CoinParticle& operator=(const CoinParticle& _Other) = delete;
	CoinParticle& operator=(CoinParticle&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

private:
	float4 MoveDir_;
	float4 TargetPos_;
};

