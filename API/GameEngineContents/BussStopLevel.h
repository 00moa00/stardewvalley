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
class BussStopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BussStopLevel();
	~BussStopLevel();

	// delete Function
	BussStopLevel(const BussStopLevel& _Other) = delete;
	BussStopLevel(BussStopLevel&& _Other) noexcept = delete;
	BussStopLevel& operator=(const BussStopLevel& _Other) = delete;
	BussStopLevel& operator=(BussStopLevel&& _Other) noexcept = delete;

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

