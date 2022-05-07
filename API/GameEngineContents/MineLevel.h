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
#include "PlayerHPFrame.h"


// Ό³Έν :
class MineLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MineLevel();
	~MineLevel();

	// delete Function
	MineLevel(const MineLevel& _Other) = delete;
	MineLevel(MineLevel&& _Other) noexcept = delete;
	MineLevel& operator=(const MineLevel& _Other) = delete;
	MineLevel& operator=(MineLevel&& _Other) noexcept = delete;

private:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	std::map<int, Items*> MapObject_;

private:
	void LoadMapObject();



};

