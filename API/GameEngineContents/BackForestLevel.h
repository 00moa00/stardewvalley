#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

#include "TileData.h"
#include "RendererData.h"

#include "PlayerEnergyFrame.h"
#include "MainUI.h"
#include "BackGround.h"
#include "Player.h"
#include "Inventory.h"
#include "Items.h"
#include "Npc.h"
#include "Mouse.h"
#include "FlowingFlower.h"


// Ό³Έν :
class BackForestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BackForestLevel();
	~BackForestLevel();

	// delete Function
	BackForestLevel(const BackForestLevel& _Other) = delete;
	BackForestLevel(BackForestLevel&& _Other) noexcept = delete;
	BackForestLevel& operator=(const BackForestLevel& _Other) = delete;
	BackForestLevel& operator=(BackForestLevel&& _Other) noexcept = delete;

private:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	BackGround* BackGround_;
	BackGround* BackGroundFront_;
	FlowingFlower* FlowingFlower_;

	std::map<int, Items*> MapObject_;

private:
	void LoadMapObject();

};

