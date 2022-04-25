#pragma once
#include "Effect.h"

// Ό³Έν :
class KiraEffect : public Effect
{
public:
	// constrcuter destructer
	KiraEffect();
	~KiraEffect();

	// delete Function
	KiraEffect(const KiraEffect& _Other) = delete;
	KiraEffect(KiraEffect&& _Other) noexcept = delete;
	KiraEffect& operator=(const KiraEffect& _Other) = delete;
	KiraEffect& operator=(KiraEffect&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

};

