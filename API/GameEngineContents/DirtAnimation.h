#pragma once
#include "Effect.h"

// Ό³Έν :
class DirtAnimation : public Effect
{
public:
	// constrcuter destructer
	DirtAnimation();
	~DirtAnimation();

	// delete Function
	DirtAnimation(const DirtAnimation& _Other) = delete;
	DirtAnimation(DirtAnimation&& _Other) noexcept = delete;
	DirtAnimation& operator=(const DirtAnimation& _Other) = delete;
	DirtAnimation& operator=(DirtAnimation&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

};

