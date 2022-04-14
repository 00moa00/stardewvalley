#pragma once

#include <GameEngine/GameEngineLevel.h>

#include "TileData.h"

#include "PlayerEnergyBar.h"
#include "PlayerEnergyFrame.h"
#include "MainUI.h"
#include "BackGround.h"
#include "Player.h"

#include "RendererData.h"
#include "Inventory.h"
#include "Items.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineSound.h>



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
	void LevelChangeStart() override;

private:
	void LoadMapObject();


	MainUI* MainUI_;
	//std::map<int, Items*> MapObject_;
	std::list<Items*> MapObject_;
	std::list<Items*>::iterator Iter;

	TILE_COLL TileState_;
	Player* Player_;
	//Inventory* Inventory_;
	PlayerEnergyBar* PlayerEnergyBar_;
	PlayerEnergyFrame* PlayerEnergyFrame_;
	BackGround* BackGround_;
	BackGround* BackGroundFront_;
};

