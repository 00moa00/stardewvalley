#pragma once
#include "Effect.h"

// Ό³Έν :
class StoneAddAnimation : public Effect
{
public:
	// constrcuter destructer
	StoneAddAnimation();
	~StoneAddAnimation();

	// delete Function
	StoneAddAnimation(const StoneAddAnimation& _Other) = delete;
	StoneAddAnimation(StoneAddAnimation&& _Other) noexcept = delete;
	StoneAddAnimation& operator=(const StoneAddAnimation& _Other) = delete;
	StoneAddAnimation& operator=(StoneAddAnimation&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
};

