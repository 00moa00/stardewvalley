#pragma once
#include "Monster.h"

// Ό³Έν :
class Clab : public Monster
{
public:
	// constrcuter destructer
	Clab();
	~Clab();

	// delete Function
	Clab(const Clab& _Other) = delete;
	Clab(Clab&& _Other) noexcept = delete;
	Clab& operator=(const Clab& _Other) = delete;
	Clab& operator=(Clab&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

private:
	void DirAnimation();

	float4 Dir;
	float Check;
};

