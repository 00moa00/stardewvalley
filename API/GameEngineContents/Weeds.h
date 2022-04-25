#pragma once
#include "Items.h"

// Ό³Έν :
class Weeds : public Items
{
public:
	// constrcuter destructer
	Weeds();
	~Weeds();

	// delete Function
	Weeds(const Weeds& _Other) = delete;
	Weeds(Weeds&& _Other) noexcept = delete;
	Weeds& operator=(const Weeds& _Other) = delete;
	Weeds& operator=(Weeds&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void Render() override;


};

