#pragma once
#include "Effect.h"

// Ό³Έν :
class CoinAnimation : public Effect
{
public:
	// constrcuter destructer
	CoinAnimation();
	~CoinAnimation();

	// delete Function
	CoinAnimation(const CoinAnimation& _Other) = delete;
	CoinAnimation(CoinAnimation&& _Other) noexcept = delete;
	CoinAnimation& operator=(const CoinAnimation& _Other) = delete;
	CoinAnimation& operator=(CoinAnimation&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

	float4 MoveDir_;
	float4 TargetPos_;
};

