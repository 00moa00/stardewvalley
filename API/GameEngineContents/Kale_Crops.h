#pragma once
#include"Crops.h"

// Ό³Έν :
class Kale_Crops : public Crops
{
public:
	// constrcuter destructer
	Kale_Crops();
	~Kale_Crops();

	// delete Function
	Kale_Crops(const Kale_Crops& _Other) = delete;
	Kale_Crops(Kale_Crops&& _Other) noexcept = delete;
	Kale_Crops& operator=(const Kale_Crops& _Other) = delete;
	Kale_Crops& operator=(Kale_Crops&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void DropCropsInMap() override;

};

