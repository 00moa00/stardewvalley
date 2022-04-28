#pragma once

#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

#include "TileData.h"
#include "RendererData.h"

#include "BackGround.h"

#include "PlayerEnergyFrame.h"
#include "MainUI.h"
#include "Player.h"
#include "Inventory.h"

#include "Items.h"
#include "Npc.h"
#include "Mouse.h"

#include "FadeInOut.h"

#include <list>

// Ό³Έν :
class MyHouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MyHouseLevel();
	~MyHouseLevel();

	// delete Function
	MyHouseLevel(const MyHouseLevel& _Other) = delete;
	MyHouseLevel(MyHouseLevel&& _Other) noexcept = delete;
	MyHouseLevel& operator=(const MyHouseLevel& _Other) = delete;
	MyHouseLevel& operator=(MyHouseLevel&& _Other) noexcept = delete;
	
	float Time;

	//GameEngineSoundPlayer BgmPlayer;

private:

	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	void LoadMapObject();

	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	std::map<int, Items*> MapObject_;
	//std::map<int, Items*>::iterator Iter;
};