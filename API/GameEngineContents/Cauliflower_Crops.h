#pragma once
#include "Crops.h"

// Ό³Έν :
class Cauliflower_Crops : public Crops
{
public:
	// constrcuter destructer
	Cauliflower_Crops();
	~Cauliflower_Crops();

	// delete Function
	Cauliflower_Crops(const Cauliflower_Crops& _Other) = delete;
	Cauliflower_Crops(Cauliflower_Crops&& _Other) noexcept = delete;
	Cauliflower_Crops& operator=(const Cauliflower_Crops& _Other) = delete;
	Cauliflower_Crops& operator=(Cauliflower_Crops&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void DropCropsInMap() override;

};

