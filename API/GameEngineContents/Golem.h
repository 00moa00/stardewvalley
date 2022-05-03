#pragma once
#include "Monster.h"

// Ό³Έν :
class Golem : public Monster
{
public:
	// constrcuter destructer
	Golem();
	~Golem();

	// delete Function
	Golem(const Golem& _Other) = delete;
	Golem(Golem&& _Other) noexcept = delete;
	Golem& operator=(const Golem& _Other) = delete;
	Golem& operator=(Golem&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

private:
	void DirAnimation();

	bool CheckTime_;

	float4 Dir;
	float Check;
	float CheckTimer_;
};

