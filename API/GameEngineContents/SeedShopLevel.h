#pragma once
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
class SeedShopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SeedShopLevel();
	~SeedShopLevel();

	// delete Function
	SeedShopLevel(const SeedShopLevel& _Other) = delete;
	SeedShopLevel(SeedShopLevel&& _Other) noexcept = delete;
	SeedShopLevel& operator=(const SeedShopLevel& _Other) = delete;
	SeedShopLevel& operator=(SeedShopLevel&& _Other) noexcept = delete;

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

