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
class BusStopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BusStopLevel();
	~BusStopLevel();

	// delete Function
	BusStopLevel(const BusStopLevel& _Other) = delete;
	BusStopLevel(BusStopLevel&& _Other) noexcept = delete;
	BusStopLevel& operator=(const BusStopLevel& _Other) = delete;
	BusStopLevel& operator=(BusStopLevel&& _Other) noexcept = delete;

protected:

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

