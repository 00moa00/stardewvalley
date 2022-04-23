#pragma once
#include"Crops.h"

// Ό³Έν :
class Potato_Crops : public Crops
{
public:
	// constrcuter destructer
	Potato_Crops();
	~Potato_Crops();

	// delete Function
	Potato_Crops(const Potato_Crops& _Other) = delete;
	Potato_Crops(Potato_Crops&& _Other) noexcept = delete;
	Potato_Crops& operator=(const Potato_Crops& _Other) = delete;
	Potato_Crops& operator=(Potato_Crops&& _Other) noexcept = delete;
protected:

private:
	void Start() override;
	void Update() override;
	void DropCropsInMap() override;

};

