#pragma once
#include "Effect.h"

// Ό³Έν :
class StoneCrushAnimation : public Effect
{
public:
	// constrcuter destructer
	StoneCrushAnimation();
	~StoneCrushAnimation();

	// delete Function
	StoneCrushAnimation(const StoneCrushAnimation& _Other) = delete;
	StoneCrushAnimation(StoneCrushAnimation&& _Other) noexcept = delete;
	StoneCrushAnimation& operator=(const StoneCrushAnimation& _Other) = delete;
	StoneCrushAnimation& operator=(StoneCrushAnimation&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
};

