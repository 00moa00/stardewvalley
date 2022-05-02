#pragma once
#include "Monster.h"

// Ό³Έν :
class Bug : public Monster
{
public:
	// constrcuter destructer
	Bug();
	~Bug();

	// delete Function
	Bug(const Bug& _Other) = delete;
	Bug(Bug&& _Other) noexcept = delete;
	Bug& operator=(const Bug& _Other) = delete;
	Bug& operator=(Bug&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

private:
	void DirAnimation();

};

