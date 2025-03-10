#pragma once
#include "Items.h"

enum class OPEN_UPDATE
{
	WAIT,
	OPEN,
	GET,
	MOVE_ITEM,
};

// ���� :
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

	void ItemCollPlayer() override;
private:
	Items* MoveItem;
	OPEN_UPDATE OpenUpdate_;
};

