#pragma once
#include "Items.h"

// Ό³Έν :
class ShippingBoxTop : public Items
{
public:
	static ShippingBoxTop* MainShippingBoxTop;

	// constrcuter destructer
	ShippingBoxTop();
	~ShippingBoxTop();

	// delete Function
	ShippingBoxTop(const ShippingBoxTop& _Other) = delete;
	ShippingBoxTop(ShippingBoxTop&& _Other) noexcept = delete;
	ShippingBoxTop& operator=(const ShippingBoxTop& _Other) = delete;
	ShippingBoxTop& operator=(ShippingBoxTop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

public:
	void SetShippingBoxTopAnimationInit();
	void SetShippingBoxTopAnimationOpen();
	void SetShippingBoxTopAnimationClose();

};

