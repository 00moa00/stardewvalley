#pragma once
#include "Items.h"

// Ό³Έν :
class Hoe : public Items
{
public:
	// constrcuter destructer
	Hoe();
	~Hoe();

	// delete Function
	Hoe(const Hoe& _Other) = delete;
	Hoe(Hoe&& _Other) noexcept = delete;
	Hoe& operator=(const Hoe& _Other) = delete;
	Hoe& operator=(Hoe&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;
	float4 Pos;
};

