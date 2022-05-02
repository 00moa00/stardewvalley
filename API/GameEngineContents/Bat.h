#pragma once
#include "Monster.h"

// Ό³Έν :
class Bat : public Monster
{
public:
	// constrcuter destructer
	Bat();
	~Bat();

	// delete Function
	Bat(const Bat& _Other) = delete;
	Bat(Bat&& _Other) noexcept = delete;
	Bat& operator=(const Bat& _Other) = delete;
	Bat& operator=(Bat&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

private:
	void DirAnimation();

};

