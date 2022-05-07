#pragma once
#include"Crops.h"

// Ό³Έν :
class Jazz_Crops : public Crops
{
public:
	// constrcuter destructer
	Jazz_Crops();
	~Jazz_Crops();

	// delete Function
	Jazz_Crops(const Jazz_Crops& _Other) = delete;
	Jazz_Crops(Jazz_Crops&& _Other) noexcept = delete;
	Jazz_Crops& operator=(const Jazz_Crops& _Other) = delete;
	Jazz_Crops& operator=(Jazz_Crops&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void DropCropsInMap() override;
	bool GetisDeath() override;

};

