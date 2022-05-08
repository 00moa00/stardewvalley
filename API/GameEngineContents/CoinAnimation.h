#pragma once
#include "Effect.h"

enum class COIN_STATE
{
	COUNT,
	CREATE
};

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

	COIN_STATE CoinState_;

	float4 MoveDir_;
	float4 TargetPos_;
	float Timer_;

	Effect* Coin_;
};

