#pragma once
#include <GameEngine/GameEngineLevel.h>

#include <GameEngineBase/GameEngineSound.h>
#include "TileData.h"
#include "RendererData.h"
#include "MenuButton.h"

#include "PlayerEnergyFrame.h"
#include "MainUI.h"
#include "BackGround.h"
#include "Player.h"
#include "Inventory.h"
#include "Items.h"
#include "Mouse.h"
#include "FlowingFlower.h"
#include "PlayerHPFrame.h"

class DayOffLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	DayOffLevel();
	~DayOffLevel();

	// delete Function
	DayOffLevel(const DayOffLevel& _Other) = delete;
	DayOffLevel(DayOffLevel&& _Other) noexcept = delete;
	DayOffLevel& operator=(const DayOffLevel& _Other) = delete;
	DayOffLevel& operator=(DayOffLevel&& _Other) noexcept = delete;

private:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	BackGround* BackGround_;
	BackGround* BackGroundFront_;
	MenuButton* OKButton_;

	int DayOffFarming_;
	int DayOffFForaging_;
	int DayOffFishing_;
	int DayOffMining_;
	int DayOffOther_;
	int DayOffTotal_;


};

