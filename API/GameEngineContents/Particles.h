#pragma once
#include "Effect.h"

// Ό³Έν :
class Particles : public Effect
{
public:
	// constrcuter destructer
	Particles();
	~Particles();

	// delete Function
	Particles(const Particles& _Other) = delete;
	Particles(Particles&& _Other) noexcept = delete;
	Particles& operator=(const Particles& _Other) = delete;
	Particles& operator=(Particles&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

};

