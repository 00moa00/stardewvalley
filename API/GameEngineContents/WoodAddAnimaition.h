#pragma once
#include "Effect.h"

// Ό³Έν :
class WoodAddAnimaition : public Effect
{
public:
	// constrcuter destructer
	WoodAddAnimaition();
	~WoodAddAnimaition();

	// delete Function
	WoodAddAnimaition(const WoodAddAnimaition& _Other) = delete;
	WoodAddAnimaition(WoodAddAnimaition&& _Other) noexcept = delete;
	WoodAddAnimaition& operator=(const WoodAddAnimaition& _Other) = delete;
	WoodAddAnimaition& operator=(WoodAddAnimaition&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
};

