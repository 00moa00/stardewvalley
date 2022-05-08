#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>


#include "TileData.h"
#include "RendererData.h"

#include "PlayerEnergyBar.h"
#include "PlayerEnergyFrame.h"
#include "MainUI.h"

#include "BackGround.h"

#include "Player.h"
#include "Inventory.h"
#include "Items.h"
#include "Npc.h"
#include "Mouse.h"

#include <list>
#include "FlowingFlower.h"
#include "PlayerHPFrame.h"

class Player;
class Inventory;


// Ό³Έν :
class MyFarmLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MyFarmLevel();
	~MyFarmLevel();

	// delete Function
	MyFarmLevel(const MyFarmLevel& _Other) = delete;
	MyFarmLevel(MyFarmLevel&& _Other) noexcept = delete;
	MyFarmLevel& operator=(const MyFarmLevel& _Other) = delete;
	MyFarmLevel& operator=(MyFarmLevel&& _Other) noexcept = delete;

	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


private:

	float Time;

	BackGround* BackGround_;
	BackGround* BackGroundFront_;
	FlowingFlower* FlowingFlower_;
	GameEngineSoundPlayer BgmPlayer;

	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;

private:
	void LoadMapObject();
};