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
class SaloonLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SaloonLevel();
	~SaloonLevel();

	// delete Function
	SaloonLevel(const SaloonLevel& _Other) = delete;
	SaloonLevel(SaloonLevel&& _Other) noexcept = delete;
	SaloonLevel& operator=(const SaloonLevel& _Other) = delete;
	SaloonLevel& operator=(SaloonLevel&& _Other) noexcept = delete;

private:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	Shop* Shop_;

	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	std::map<std::string, Npc*> NpcList_;
	std::map<int, Items*> MapObject_;

private:
	void LoadMapObject();
};

