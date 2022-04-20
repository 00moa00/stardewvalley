#pragma once
#include"Crops.h"

// Ό³Έν :
class Parsnip_Growing : public Crops
{
public:
	// constrcuter destructer
	Parsnip_Growing();
	~Parsnip_Growing();

	// delete Function
	Parsnip_Growing(const Parsnip_Growing& _Other) = delete;
	Parsnip_Growing(Parsnip_Growing&& _Other) noexcept = delete;
	Parsnip_Growing& operator=(const Parsnip_Growing& _Other) = delete;
	Parsnip_Growing& operator=(Parsnip_Growing&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

