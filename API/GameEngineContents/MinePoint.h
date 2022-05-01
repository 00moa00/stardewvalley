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

// Ό³Έν :
class MinePoint : public GameEngineLevel
{
public:
	// constrcuter destructer
	MinePoint();
	~MinePoint();

	// delete Function
	MinePoint(const MinePoint& _Other) = delete;
	MinePoint(MinePoint&& _Other) noexcept = delete;
	MinePoint& operator=(const MinePoint& _Other) = delete;
	MinePoint& operator=(MinePoint&& _Other) noexcept = delete;

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

