#pragma once
#include"Crops.h"

// Ό³Έν :
class Tulip_Crops : public Crops
{
public:
	// constrcuter destructer
	Tulip_Crops();
	~Tulip_Crops();

	// delete Function
	Tulip_Crops(const Tulip_Crops& _Other) = delete;
	Tulip_Crops(Tulip_Crops&& _Other) noexcept = delete;
	Tulip_Crops& operator=(const Tulip_Crops& _Other) = delete;
	Tulip_Crops& operator=(Tulip_Crops&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

