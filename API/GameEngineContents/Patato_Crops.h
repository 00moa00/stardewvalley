#pragma once
#include"Crops.h"

// Ό³Έν :
class Patato_Crops : public Crops
{
public:
	// constrcuter destructer
	Patato_Crops();
	~Patato_Crops();

	// delete Function
	Patato_Crops(const Patato_Crops& _Other) = delete;
	Patato_Crops(Patato_Crops&& _Other) noexcept = delete;
	Patato_Crops& operator=(const Patato_Crops& _Other) = delete;
	Patato_Crops& operator=(Patato_Crops&& _Other) noexcept = delete;
protected:

private:
	void Start() override;
	void Update() override;

};

