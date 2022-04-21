#pragma once
#include"Crops.h"

// Ό³Έν :
class Parsnip_Crops : public Crops
{
public:
	// constrcuter destructer
	Parsnip_Crops();
	~Parsnip_Crops();

	// delete Function
	Parsnip_Crops(const Parsnip_Crops& _Other) = delete;
	Parsnip_Crops(Parsnip_Crops&& _Other) noexcept = delete;
	Parsnip_Crops& operator=(const Parsnip_Crops& _Other) = delete;
	Parsnip_Crops& operator=(Parsnip_Crops&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

