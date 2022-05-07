#pragma once
#include"Crops.h"
// Ό³Έν :
class Bean_Crops : public Crops
{
public:
	// constrcuter destructer
	Bean_Crops();
	~Bean_Crops();

	// delete Function
	Bean_Crops(const Bean_Crops& _Other) = delete;
	Bean_Crops(Bean_Crops&& _Other) noexcept = delete;
	Bean_Crops& operator=(const Bean_Crops& _Other) = delete;
	Bean_Crops& operator=(Bean_Crops&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void DropCropsInMap() override;
	bool GetisDeath() override;
};

