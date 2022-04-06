#pragma once
#include "ItemData.h"
#include "Items.h"
// Ό³Έν :
class WildHorseradish : public Items
{
public:
	// constrcuter destructer
	WildHorseradish();
	~WildHorseradish();

	// delete Function
	WildHorseradish(const WildHorseradish& _Other) = delete;
	WildHorseradish(WildHorseradish&& _Other) noexcept = delete;
	WildHorseradish& operator=(const WildHorseradish& _Other) = delete;
	WildHorseradish& operator=(WildHorseradish&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

	//GameEngineRenderer* WildHorseradish_;
	//GameEngineRenderer* InventoryBox_;


};

