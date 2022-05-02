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


// 설명 :
class TownLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TownLevel();
	~TownLevel();

	// delete Function
	TownLevel(const TownLevel& _Other) = delete;
	TownLevel(TownLevel&& _Other) noexcept = delete;
	TownLevel& operator=(const TownLevel& _Other) = delete;
	TownLevel& operator=(TownLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	void LoadMapObject();


	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	FlowingFlower* FlowingFlower_;

	std::map<int, Items*> MapObject_;
	std::map<std::string, Npc*> NpcList_;	//검색할 일이 없으면 다른 자료 구조로 바꿀 예정
	
};

