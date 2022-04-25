#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
// Ό³Έν :
class InventoryCurrentFrame : public GameEngineActor
{
public:

	static InventoryCurrentFrame* MainInventoryCurrentFrame;

	// constrcuter destructer
	InventoryCurrentFrame();
	~InventoryCurrentFrame();

	// delete Function
	InventoryCurrentFrame(const InventoryCurrentFrame& _Other) = delete;
	InventoryCurrentFrame(InventoryCurrentFrame&& _Other) noexcept = delete;
	InventoryCurrentFrame& operator=(const InventoryCurrentFrame& _Other) = delete;
	InventoryCurrentFrame& operator=(InventoryCurrentFrame&& _Other) noexcept = delete;


private:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


private:

	GameEngineRenderer* CurrentItem_;

};

