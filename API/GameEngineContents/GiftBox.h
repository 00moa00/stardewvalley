#pragma once
#include "Items.h"

enum class OPEN_UPDATE
{
	WAIT,
	OPEN,
	GET,
};

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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void GetItemAndAddInventory() override;
private:

	OPEN_UPDATE OpenUpdate_;
};

