#pragma once
#include "Items.h"

// Ό³Έν :
class GiftBox : public Items
{
public:
	static GiftBox* MainGiftBox;

	// constrcuter destructer
	GiftBox();
	~GiftBox();

	// delete Function
	GiftBox(const GiftBox& _Other) = delete;
	GiftBox(GiftBox&& _Other) noexcept = delete;
	GiftBox& operator=(const GiftBox& _Other) = delete;
	GiftBox& operator=(GiftBox&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;

};

