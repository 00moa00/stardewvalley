#pragma once
#include "Items.h"
// Ό³Έν :
class ShopFlag : public Items
{
public:
//	static ShopFlag* MainShopFlag;

	ShopFlag();
	~ShopFlag();

	// delete Function
	ShopFlag(const ShopFlag& _Other) = delete;
	ShopFlag(ShopFlag&& _Other) noexcept = delete;
	ShopFlag& operator=(const ShopFlag& _Other) = delete;
	ShopFlag& operator=(ShopFlag&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

};

