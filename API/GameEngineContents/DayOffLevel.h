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

#include "Font.h"

enum class DAYOFF_STATE
{
	MONEY_UPDATE,
	UPDATE,
};


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

	GameEngineSoundPlayer BgmPlayer;

	int DayOffFarming_;
	int DayOffFForaging_;
	int DayOffFishing_;
	int DayOffMining_;
	int DayOffOther_;
	int DayOffTotal_;

	Font* DayOffFarmingFont_;
	Font* DayOffFForagingFont_;
	Font* DayOffFishingFont_;
	Font* DayOffMiningFont_;
	Font* DayOffOtherFont_;
	Font* DayOffTotalFont_;

	Font* DayFont_;

	MONEY_UPDATE FarmingState_;
	MONEY_UPDATE ForagingState_;
	MONEY_UPDATE FishingState_;
	MONEY_UPDATE MiningState_;
	MONEY_UPDATE OtherState_;
	MONEY_UPDATE TotalState_;

	int PrevFarmingMoney_ ;
	int PrevForagingMoney_ ;
	int PrevFishingMoney_ ;
	int PrevMiningMoney_ ;
	int PrevOtherMoney_ ;
	int PrevTotalMoney_ ;

	DAYOFF_STATE UpdateState_;

private:
	void AddFarmingAnimation();
	void AddForagingAnimation();
	void AddFisingAnimation();
	void AddMiningAnimation();
	void AddOtherAnimation();
	void AddTotalAnimation();

};

