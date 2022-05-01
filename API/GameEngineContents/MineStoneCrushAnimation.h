#pragma once
#pragma once
#include "Effect.h"
// Ό³Έν :
class MineStoneCrushAnimation : public Effect
{
public:
	// constrcuter destructer
	MineStoneCrushAnimation();
	~MineStoneCrushAnimation();

	// delete Function
	MineStoneCrushAnimation(const MineStoneCrushAnimation& _Other) = delete;
	MineStoneCrushAnimation(MineStoneCrushAnimation&& _Other) noexcept = delete;
	MineStoneCrushAnimation& operator=(const MineStoneCrushAnimation& _Other) = delete;
	MineStoneCrushAnimation& operator=(MineStoneCrushAnimation&& _Other) noexcept = delete;


private:
	void Start() override;
	void Update() override;

	void SetImageIndex(ITEM _ItemCode)override;

private:
	float DeathTimer_;

};

